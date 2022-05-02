// Phase 3.1: Evaluator for Lexp
//Trinity Caitlin Atayan Belen
//Comp 141: Programming Languages

public class PTInteriorNode implements PTNode {
	Token operator;
	PTNode left;
	PTNode middle;
	PTNode right;
	
	public PTInteriorNode(Token operator, PTNode left, PTNode middle, PTNode right) {
		super();
		this.operator = operator;
		this.left = left;
		this.middle = middle;
		this.right = right;
	}
	
	public PTInteriorNode(Token operator, Token left, PTNode right) {
		super();
		this.operator = operator;
		this.left = new PTLeafNode(left);
		this.middle = null;
		this.right = right;
	}
	
	public PTInteriorNode(Token operator, PTNode left, PTNode right) {
		super();
		this.operator = operator;
		this.left = left;
		this.middle = null;
		this.right = right;
	}

	public Token getData() {
		return operator;
	}
	
	public PTNode getLeftSubTree() {
		return left;
	}
	
	public PTNode getMiddleSubTree() {
		return middle;
	}
	
	public PTNode getRightSubTree() {
		return right;
	}
}
