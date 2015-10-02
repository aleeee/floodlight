package net.floodlightcontroller.solver;

import java.util.ArrayList;

public class VirtualFunction {
	private String vFId;
	private static ArrayList<VirtualFunction> vfs;
	public VirtualFunction(String vFId) {
		super();
		this.vFId = vFId;
	}

	public String getvFId() {
		return vFId;
	}

	public void setvFId(String vFId) {
		this.vFId = vFId;
	}
	
	public static ArrayList<VirtualFunction> addVf(int numVfs){
		
		vfs = new ArrayList<VirtualFunction>();
		
		for(int i=0; i <=numVfs; i++){
			vfs.add(new VirtualFunction("tVF0".concat(String.valueOf(i))));
		}
		return vfs;
	}

}
