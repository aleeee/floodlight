package net.floodlightcontroller.solver;

public class Request {
	private String reqId;
	private double reqLoad;
	private int[] vfList;
	private int sourceNode;
	private int destNode;
	public Request(String reqId, double reqLoad, int[] vfList, int sourceNode, int destNode) {
		super();
		this.reqId = reqId;
		this.reqLoad = reqLoad;
		this.vfList = vfList;
		this.sourceNode = sourceNode;
		this.destNode = destNode;
	}
	public String getReqId() {
		return reqId;
	}
	public void setReqId(String reqId) {
		this.reqId = reqId;
	}
	public double getReqLoad() {
		return reqLoad;
	}
	public void setReqLoad(double reqLoad) {
		this.reqLoad = reqLoad;
	}
	public int[] getVfList() {
		return vfList;
	}
	public void setVfList(int[] vfList) {
		this.vfList = vfList;
	}
	public int getSourceNode() {
		return sourceNode;
	}
	public void setSourceNode(int sourceNode) {
		this.sourceNode = sourceNode;
	}
	public int getDestNode() {
		return destNode;
	}
	public void setDestNode(int destNode) {
		this.destNode = destNode;
	}
	
	
}
