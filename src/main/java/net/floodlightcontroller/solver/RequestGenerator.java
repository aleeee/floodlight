package net.floodlightcontroller.solver;

import java.io.IOException;
import java.io.PrintWriter;
import java.text.DecimalFormat;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.Map;

public class RequestGenerator {
	
	private int numberOfDC;
	private double[][] latency_matrix;
	private Map<String,ArrayList<VFConfig>> map;
	private static ArrayList<Request> request = new ArrayList<>();
	
	public RequestGenerator(Graph g){
		this.numberOfDC = g.getNumDC();
		this.latency_matrix = g.getLatency();
		this.map = g.getSymbolTable();
		
		listReq();
		
		for(int i=0; i< request.size(); i++){
			genReq(request.get(i));
		}
		
	}
	
	public void genReq(Request r){
		
		String reqName = r.getReqId();
		int[] listVf = r.getVfList();
		int sourceNode = r.getSourceNode();
		int destNode = r.getDestNode();
		
		
		DecimalFormat df = new DecimalFormat("0.0");
		PrintWriter writer  = null;
		String workingDir = System.getProperty("user.dir");
		
		try{
			
			writer= new PrintWriter(workingDir.concat("/request/".concat(reqName)));
			writer.print(numberOfDC+ " " );
			writer.println(r.getVfList().length);
			for(int i=0; i<latency_matrix.length; i++){
				for(int j=0; j<latency_matrix.length; j++){
					writer.print(latency_matrix[i][j] +" ");
				}
				writer.println();
			}
			
			for(int i=0; i < numberOfDC; i++){
				
				writer.println(r.getVfList().length);
			}
			
			for(int i=0; i < r.getVfList().length; i++){
				writer.print(i + " ");
				String vfName = "VF".concat(String.valueOf(listVf[i]));
				ArrayList<VFConfig> conf = map.get(vfName);
				
				int interdicted = numberOfDC - conf.size();
				writer.print(interdicted + " ");
				
				Iterator<VFConfig> proc_time = conf.iterator();
				ArrayList<Integer> vFunc = new ArrayList<>();
				while(proc_time.hasNext()){
					vFunc.add(proc_time.next().getdCId());
				}
				ArrayList<Integer> interdictedVM = new ArrayList<>();
				
				for(int k=0; k < numberOfDC; k++){
					if (vFunc.contains(k)){
						continue;
					}
					else{
						interdictedVM.add(k);
						writer.print(k + " ");
					}
					
					
				}
				Iterator<VFConfig> vc = conf.iterator();
				VFConfig vconf;
				for(int j=0; j<numberOfDC; j++){
					if(interdictedVM.contains(j)){
						writer.print(0 + " ");
						
					}
					else{
						vconf=vc.next();
						writer.print(df.format(vconf.getWorkLoad()/vconf.getCapacity()) + " ");
					}
				}
				
				writer.println();
				
				
			}
			
			if(r.getSourceNode()==100){
				for(int s=0; s < numberOfDC; s++){
					writer.print(0 + " ");
				}
			}else{
				for(int s = 0; s < numberOfDC; s++){
					writer.print(latency_matrix[sourceNode][s] + " ");
				}
				
			}
			writer.println();
			for(int d=0; d< numberOfDC; d++){
				writer.print(latency_matrix[destNode][d] + " ");
			}
			
		}catch(IOException e){
			e.printStackTrace();
		}finally{
			try{
				writer.close();
			}catch(Exception ex){
				ex.printStackTrace();
			}
		}
		
	}
	
	public void listReq(){
		
		int[] r1 = {1,2,3,6};
		int[] r2 = {0,3,4,7};
		int[] r3 = {0,2,7,3};
		int[] r4 = {1,5,6};
		int[] r5 = {8,2,3};
		int[] r6 = {8,2,3};
		int[] r7 = {8,2,3};
		int[] r8 = {8,2,3};
		
		request.add(new Request("req1", 0.2, r1, 0, 5));
		request.add(new Request("req2", 10, r2, 2, 4));
		request.add(new Request("req3", 20, r3, 2, 4));
		request.add(new Request("req4", 50, r4, 0, 5));
		request.add(new Request("req5", 50, r5, 100, 0));
		request.add(new Request("req6", 50, r6, 100, 5));
		request.add(new Request("req7", 500, r7, 100, 0));
		request.add(new Request("req8", 500, r8, 100, 5));
		
		
	}
	public static ArrayList<Request> getRequest() {
		return request;
	}

	public void setRequest(ArrayList<Request> request) {
		this.request = request;
	}
}