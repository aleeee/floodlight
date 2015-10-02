package net.floodlightcontroller.solver;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.LinkedList;

public class Statistics {
	
	String dir = System.getProperty("user.dir");
	String line="";
	StringBuilder sb;
	BufferedReader br;
	String stat="Solstat";
	ArrayList<Request> request = new ArrayList<Request>();
	Request r ;
	PrintWriter writer = null;
	public Statistics(){
		
		printStat();
			  
	}
	public void printStat(){
		
		//read the request file names
		String folder = dir.concat("/result/");
		File[] listOfFiles = new File(folder).listFiles();
		
		Arrays.sort(listOfFiles);
	    
		try {
			writer = new PrintWriter(new BufferedWriter(new FileWriter(dir.concat("/file/").concat("/stat.txt"),true)));
			
		writer.println();
		writer.println("Request  Req.Load VF_Chain    SNode     DNode     Solution     Tot.Latency");
		request = RequestGenerator.getRequest();
		
		for(int j=0; j < request.size(); j++){
			r = request.get(j);
			String rName = r.getReqId();
			
			
				//search the associated result file
			for(int i=0; i < listOfFiles.length; i++){
				
				if(listOfFiles[i].isFile()){
					
					String name = listOfFiles[i].getName();
					
					if(name.startsWith(rName)){
						String fileName = folder.concat(name);
						getStat(r,fileName);
						break;
					
					}
				}
			}
		}
		
} catch (IOException e) {
			
			e.printStackTrace();
		}finally{
			try{
				writer.close();
				
			}catch(Exception wexp){
				wexp.printStackTrace();
			}
		}
		
	
	}	
	public void getStat(Request r, String fName){		
		sb = new StringBuilder();
		String[] v = new String[5];
		
		LinkedList<String> vm = new LinkedList<String>();
		sb.append(r.getReqId());
		//vm.add(r.getReqId());
		sb.append("\t");
		sb.append(r.getReqLoad());
		sb.append("\t");
		//vm.add(String.valueOf(r.getReqLoad()));
		int[] vf = r.getVfList();
		for(int i=0; i<vf.length; i++){
		//	vm.add(String.valueOf(vf[i]));
			sb.append(String.valueOf(vf[i]));
			sb.append(",");
			
		}
		if(vf.length<4){
		   sb.append("\t");
		}
		sb.append("\t");
		
		sb.append(String.valueOf(r.getSourceNode()));
		sb.append("\t");
		sb.append(r.getDestNode());
		sb.append("\t");
		//vm.add(String.valueOf(r.getSourceNode()));
		//vm.add(String.valueOf(r.getDestNode()));
		try{
			br = new BufferedReader(new FileReader(fName));
		    
			try{
				while((line = br.readLine()) != null){
					if(line.startsWith(stat)){
						int i=0;
						while(!(line=br.readLine()).startsWith("Total latency")){
						
							v = line.split(" ");
							
						//	vm.add(v[4]);
							sb.append(v[4]);
							sb.append(",");
							i++;
							}
						if(i<=3){
							sb.append(" ");
						}
						sb.append("\t");
						String[] t = line.split(" ");
						
						//sb.append("\t");
						sb.append(t[3]);
						//vm.add(t[3]);
						//writer.print(vm);
					    //sb.append(vm);
						//System.out.println(sb);
						writer.println(sb);
				}
				
				}
						    
			}catch(IOException ex){
				ex.printStackTrace();
			}
			
		}catch(FileNotFoundException e){
			e.printStackTrace();
		}finally{
			try{
				br.close();
				
			}catch(Exception exp){
				exp.printStackTrace();
			}
		}
	}
	

}
