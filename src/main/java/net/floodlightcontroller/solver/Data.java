package net.floodlightcontroller.solver;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;

public class Data {
	
	public Data(){
		
	}
	public double[][] setLatency(){
		double[][] latencies = {{0, 0.12, 0.12, 0.12 ,0.12 ,0.12, 0.06, 0.06 ,0.17 ,1.82, 1.18},
								{0.12 ,0 ,0.12 ,0.12 ,0.12 ,0.12 ,0.06, 0.06 ,0.17 ,1.82 ,1.18},
								{0.12 ,0.12, 0 ,0.12 ,0.12 ,0.12 ,0.06 ,0.17 ,0.06 ,2.37 ,1},
								{0.12 ,0.12 ,0.12 ,0 ,0.12 ,0.12 ,0.06 ,0.17, 0.06, 2.37 ,1},
								{0.12, 0.12 ,0.12, 0.12, 0, 0.12 ,0.2, 0.06 ,0.06, 1.82 ,1},
								{0.12 ,0.12 ,0.12 ,0.12 ,0.12 ,0 ,0.2 ,0.06 ,0.06 ,1.82 ,1},
								{0.06 ,0.06 ,0.06 ,0.06 ,0.02 ,0.02 ,0 ,0.14 ,0.25 ,2.3 ,3.7},
								{0.06 ,0.06 ,0.17 ,0.17 ,0.06 ,0.06 ,0.14 ,0 ,0.11 ,1.76 ,1.12},
								{0.17 ,0.17 ,0.06 ,0.06 ,0.06 ,0.06 ,0.25 ,0.11 ,0 ,2.3 ,0.94},
								{1.82 ,1.82 ,2.37 ,2.37 ,1.82 ,1.82 ,2.3 ,1.76 ,2.3 ,0 ,0.94},
								{1.18 ,1.18 ,1 ,1 ,1 ,1 ,3.7 ,1.12 ,0.94 ,1.37 ,0}
								};
		return latencies;
		
	}
	public Map<String, ArrayList<VFConfig>> mapVFToDC(){
		Map<String,ArrayList<VFConfig>> vFToDc = new HashMap<>();
		
		ArrayList<VFConfig> vf0 = new ArrayList<>();
		ArrayList<VFConfig> vf1 = new ArrayList<>();
		ArrayList<VFConfig> vf2 = new ArrayList<>();
		ArrayList<VFConfig> vf3 = new ArrayList<>();
		ArrayList<VFConfig> vf4 = new ArrayList<>();
		ArrayList<VFConfig> vf5 = new ArrayList<>();
		ArrayList<VFConfig> vf6 = new ArrayList<>();
		ArrayList<VFConfig> vf7 = new ArrayList<>();
		ArrayList<VFConfig> vf8 = new ArrayList<>();
		
		
		
		vf0.add(new VFConfig(0, 2, 5));
		vf0.add(new VFConfig(1, 1.5, 4));
		vf0.add(new VFConfig(3, 2, 5));
		vf0.add(new VFConfig(5, 1.5, 4));
		vf0.add(new VFConfig(7, 3, 10));
		
		vf1.add(new VFConfig(1, 1.5, 5));
		vf1.add(new VFConfig(2, 1.3, 5));
		vf1.add(new VFConfig(3, 1, 5));
		vf1.add(new VFConfig(4, 1.5, 6));
		vf1.add(new VFConfig(8, 3, 9));
		vf1.add(new VFConfig(9, 5, 20));
		
		vf2.add(new VFConfig(0, 1, 5));
		vf2.add(new VFConfig(2, 1.7, 7));
		vf2.add(new VFConfig(4, 1.5, 4));
		vf2.add(new VFConfig(5, 1.5, 3));
		vf2.add(new VFConfig(6, 3, 10));
		vf2.add(new VFConfig(10, 6, 20));
		
		vf3.add(new VFConfig(6, 4, 13));
		vf3.add(new VFConfig(7, 5, 20));
		vf3.add(new VFConfig(8, 4, 15));
		vf3.add(new VFConfig(10, 7, 22));
		
		vf4.add(new VFConfig(6, 5, 15));
		vf4.add(new VFConfig(7, 3, 10));
		vf4.add(new VFConfig(8, 4, 10));
		vf4.add(new VFConfig(9, 6, 17));
		
		vf5.add(new VFConfig(6, 3, 12));
		vf5.add(new VFConfig(7, 4, 15));
		vf5.add(new VFConfig(8, 4, 15));
		vf5.add(new VFConfig(9, 8, 20));
		vf5.add(new VFConfig(10, 9, 30));
		
		vf6.add(new VFConfig(9, 7, 13));
		vf6.add(new VFConfig(10, 6, 12));
		
		vf7.add(new VFConfig(9, 4, 15));
		vf7.add(new VFConfig(10, 8, 19));
		
		vf8.add(new VFConfig(9, 7, 13));
		vf8.add(new VFConfig(10, 6, 12));
		
		vFToDc.put("VF0", vf0);
		vFToDc.put("VF1", vf1);
		vFToDc.put("VF2", vf2);
		vFToDc.put("VF3", vf3);
		vFToDc.put("VF4", vf4);
		vFToDc.put("VF5", vf5);
		vFToDc.put("VF6", vf6);
		vFToDc.put("VF7", vf7);
		vFToDc.put("VF8", vf8);
		
				
		return vFToDc;
		
		
	}

}
