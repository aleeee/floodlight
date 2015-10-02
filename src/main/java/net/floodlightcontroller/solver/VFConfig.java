package net.floodlightcontroller.solver;

public class VFConfig {
	private int dCId;
	private double capacity;
	private int workLoad;
	
	public VFConfig (int id, double c , int w){
		this.dCId = id;
		this.capacity = c;
		this.workLoad = w;
		
	}

	public int getdCId() {
		return dCId;
	}

	public void setdCId(int dCId) {
		this.dCId = dCId;
	}

	public double getCapacity() {
		return capacity;
	}

	public void setCapacity(double capacity) {
		this.capacity = capacity;
	}

	public int getWorkLoad() {
		return workLoad;
	}

	public void setWorkLoad(int workLoad) {
		this.workLoad = workLoad;
	}
	

}
