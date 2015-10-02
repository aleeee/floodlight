package net.floodlightcontroller.solver;

public class Link {
	private String linkId;
	private int sourceId;
	private int destId;
	private double latency;
	public Link(){
		
	}
	
	public Link(int sourceId, int destId, double latency) {
		this.linkId = String.valueOf(sourceId).concat("to").concat(String.valueOf(destId));
		this.sourceId = sourceId;
		this.destId = destId;
		this.latency = latency;
	}

	public String getLinkId() {
		return linkId;
	}

	public void setLinkId(String linkId) {
		this.linkId = linkId;
	}

	public int getSourceId() {
		return sourceId;
	}

	public void setSourceId(int sourceId) {
		this.sourceId = sourceId;
	}

	public int getDestId() {
		return destId;
	}

	public void setDestId(int destId) {
		this.destId = destId;
	}

	public double getLatency() {
		return latency;
	}

	public void setLatency(double latency) {
		this.latency = latency;
	}
	
	
	

}
