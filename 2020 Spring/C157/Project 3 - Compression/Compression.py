#Project 3 - Compression
from collections import Counter
from itertools import chain
from PIL import Image
from PIL import ImageChops
import time

#Calculating symbol counts
def count_symbols(image):
    pixels = image.getdata()
    values = chain.from_iterable(pixels)
    counts = Counter(values).items()
    return sorted(counts, key=lambda x:x[::-1])

#Building the tree
def build_tree(counts) :
    nodes = [entry[::-1] for entry in counts]
    while len(nodes) > 1 :
        leastTwo = tuple(nodes[0:2])
        theRest = nodes[2:]
        combFreq = leastTwo[0][0] + leastTwo[1][0]
        nodes = theRest + [(combFreq, leastTwo)]
        nodes.sort(key=lambda t: t[0])
    return nodes[0]

#Trimming the tree
def trim_tree(tree) :
    p = tree[1]
    if type(p) is tuple:
        return (trim_tree(p[0]), trim_tree(p[1]))
    return p

#Assigning Codes
def assign_codes_impl(codes, node, pat):
    if type(node) == tuple:
        assign_codes_impl(codes, node[0], pat + [0])
        assign_codes_impl(codes, node[1], pat + [1])
    else:
        codes[node] = pat

def assign_codes(tree):
    codes = {}
    assign_codes_impl(codes, tree, [])
    return codes

#Bitstream
def to_binary_list(n):
    return [n] if (n <= 1) else to_binary_list(n >> 1) + [n & 1]

def from_binary_list(bits):
    result = 0
    for bit in bits:
        result = (result << 1) | bit
    return result

def pad_bits(bits, n):
    assert(n >= len(bits))
    return ([0] * (n - len(bits)) + bits)

#Output Bitstream
class OutputBitStream(object):
    def __init__(self, file_name):
        self.file_name = file_name
        self.file = open(self.file_name, 'wb')
        self.bytes_written = 0
        self.buffer = []

    def write_bit(self, value):
        self.write_bits([value])

    def write_bits(self, values):
        self.buffer += values
        while len(self.buffer) >= 8:
            self._save_byte()

    def flush(self):
        if len(self.buffer) > 0:
            self.buffer += [0] * (8 - len(self.buffer))
            self._save_byte()
        assert(len(self.buffer) == 0)

    def _save_byte(self):
        bits = self.buffer[:8]
        self.buffer[:] = self.buffer[8:]

        byte_value = from_binary_list(bits)
        self.file.write(bytes([byte_value]))
        self.bytes_written += 1

    def close(self):
        self.flush()
        self.file.close()

#Input Bit Stream
class InputBitStream(object):
    def __init__(self, file_name):
        self.file_name = file_name
        self.file = open(self.file_name, 'rb')
        self.bytes_read = 0
        self.buffer = []

    def read_bit(self):
        return self.read_bits(1)[0]

    def read_bits(self, count):
        while len(self.buffer) < count:
            self._load_byte()
        result = self.buffer[:count]
        self.buffer[:] = self.buffer[count:]
        return result

    def flush(self):
        assert(not any(self.buffer))
        self.buffer[:] = []

    def _load_byte(self):
        value = ord(self.file.read(1))
        self.buffer += pad_bits(to_binary_list(value), 8)
        self.bytes_read += 1

    def close(self):
        self.file.close()

#Compressed
def compressed_size(counts, codes):
    header_size = 2 * 16

    tree_size = len(counts) * (1 + 8)
    tree_size += len(counts) - 1
    if tree_size % 8 > 0:
        tree_size += 8 - (tree_size % 8)

    pixels_size = sum([count * len(codes[symbol]) for symbol, count in counts])
    if pixels_size % 8 > 0:
        pixels_size += 8 - (pixels_size % 8)

    return (header_size + tree_size + pixels_size) / 8

def encode_header(image, bitstream):
    height_bits = pad_bits(to_binary_list(image.height), 16)
    bitstream.write_bits(height_bits)
    width_bits = pad_bits(to_binary_list(image.width), 16)
    bitstream.write_bits(width_bits)

def encode_tree(tree, bitstream):
    if type(tree) == tuple:
        bitstream.write_bit(0)
        encode_tree(tree[0], bitstream)
        encode_tree(tree[1], bitstream)
    else:
        bitstream.write_bit(1)
        symbol_bits = pad_bits(to_binary_list(tree), 8)
        bitstream.write_bits(symbol_bits)

def encode_pixels(image, codes, bitstream):
    for pixel in image.getdata():
        for value in pixel:
            bitstream.write_bits(codes[value])

def compress_image(in_file_name, out_file_name):
    print('Compressing "%s" -> "%s"' % (in_file_name, out_file_name))
    image = Image.open(in_file_name)
    print('Image shape: (height=%d, width=%d)' % (image.height, image.width))
    size_raw = raw_size(image.height, image.width)
    print('RAW image size: %d bytes' % size_raw)
    counts = count_symbols(image)
    print('Counts: %s' % counts)
    tree = build_tree(counts)
    print('Tree: %s' % str(tree))
    trimmed_tree = trim_tree(tree)
    print('Trimmed tree: %s' % str(trimmed_tree))
    codes = assign_codes(trimmed_tree)
    print('Codes: %s' % codes)

    size_estimate = compressed_size(counts, codes)
    print('Estimated size: %d bytes' % size_estimate)

    print('Writing...')
    stream = OutputBitStream(out_file_name)
    print('* Header offset: %d' % stream.bytes_written)
    encode_header(image, stream)
    stream.flush()
    print('* Tree offset: %d' % stream.bytes_written)
    encode_tree(trimmed_tree, stream)
    stream.flush()
    print('* Pixel offset: %d' % stream.bytes_written)
    encode_pixels(image, codes, stream)
    stream.close()

    size_real = stream.bytes_written
    print('Wrote %d bytes.' % size_real)

    print('Estimate is %scorrect.' % ('' if size_estimate == size_real else 'in'))
    print('Compression ratio: %0.2f' % (float(size_raw) / size_real))

#Decompressed
def decode_header(bitstream):
    height = from_binary_list(bitstream.read_bits(16))
    width = from_binary_list(bitstream.read_bits(16))
    return (height, width)

def decode_tree(bitstream):
    flag = bitstream.read_bits(1)[0]
    if flag == 1:
        return from_binary_list(bitstream.read_bits(8))
    left = decode_tree(bitstream)
    right = decode_tree(bitstream)
    return (left, right)

def decode_value(tree, bitstream):
    bit = bitstream.read_bits(1)[0]
    node = tree[bit]
    if type(node) == tuple:
        return decode_value(node, bitstream)
    return node

def decode_pixels(height, width, tree, bitstream):
    pixels = bytearray()
    for i in range(height * width * 3):
        pixels.append(decode_value(tree, bitstream))
    return Image.frombytes('RGB', (width, height), bytes(pixels))

def decompress_image(in_file_name, out_file_name):
    print('Decompressing "%s" -> "%s"' % (in_file_name, out_file_name))

    print('Reading...')
    stream = InputBitStream(in_file_name)
    print('* Header offset: %d' % stream.bytes_read)
    height, width = decode_header(stream)
    stream.flush()
    print('* Tree offset: %d' % stream.bytes_read)
    trimmed_tree = decode_tree(stream)
    stream.flush()
    print('* Pixel offset: %d' % stream.bytes_read)
    image = decode_pixels(height, width, trimmed_tree, stream)
    stream.close()
    print('Read %d bytes.' % stream.bytes_read)

    print('Image size: (height=%d, width=%d)' % (height, width))
    print('Trimmed tree: %s' % str(trimmed_tree))
    image.save(out_file_name)

def raw_size(width, height):
    header_size = 2 * 16
    pixels_size = 3 * 8 * width * height
    return (header_size + pixels_size) / 8

def images_equal(file_name_a, file_name_b):
    image_a = Image.open(file_name_a)
    image_b = Image.open(file_name_b)

    diff = ImageChops.difference(image_a, image_b)

    return diff.getbbox() is None

if __name__ == '__main__':
    start = time.time()
    file = input("Which file are you choosing? (Don't include the extension at the end!) ")
    compress_file = file + ".bmp"
    decompress_file = file + ".png"
    compress_image(compress_file, 'answer.txt')
    print('-' * 40)
    decompress_image('answer.txt', decompress_file)
    stop = time.time()
    times = (stop - start) * 1000
    print('-' * 40)
    print('Run time takes %d miliseconds' % times)
    print('Images equal = %s' % images_equal(compress_file, decompress_file))