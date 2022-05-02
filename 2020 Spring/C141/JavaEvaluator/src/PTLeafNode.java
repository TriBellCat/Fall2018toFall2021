// Phase 3.1: Evaluator for Lexp
//Trinity Caitlin Atayan Belen
//Comp 141: Programming Languages

public class PTLeafNode implements PTNode {
	Token number;
	
	public PTLeafNode(Token number) {
		super();
		this.number = number;
	}

	public Token getData() {
		return number;
	}
	
	public PTNode getLeftSubTree() {
		return null;
	}
	
	public PTNode getMiddleSubTree() {
		return null;
	}
	
	public PTNode getRightSubTree() {
		return null;
	}
}
