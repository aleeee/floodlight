package net.floodlightcontroller.solver;

import java.util.ArrayList;

public class Node {
	
	private String id;
	private int nodeCapacity;
	private static ArrayList<Node> nodes;
	
	public Node(String id, int capacity){
		this.id = id;
		this.nodeCapacity = capacity;		
	}

	public String getId() {
		return id;
	}

	public void setId(String id) {
		this.id = id;
	}

	public int getNodeCapacity() {
		return nodeCapacity;
	}

	public void setNodeCapacity(int nodeCapacity) {
		this.nodeCapacity = nodeCapacity;
	}
	
	public static ArrayList<Node> addNodes(){
		nodes = new ArrayList<Node>();
		for(int i=0; i < 6; i++){
			nodes.add(new Node("DC".concat(String.valueOf(i)), 3));
		}
		for(int i=6; i < 9; i++){
			nodes.add(new Node("DC".concat(String.valueOf(i)), 15));
		}
		for(int i=9; i < 11; i++){
			nodes.add(new Node("DC".concat(String.valueOf(i)), 30));
		}
		return nodes;
		
	}

}
