package net.floodlightcontroller.solver;

import java.io.File;
import java.io.IOException;
import java.lang.ProcessBuilder.Redirect;

public class Solver {

		//get project directory
		String workingDir = System.getProperty("user.dir");
		
	public Solver(){
		
		//read the request file names
		File[] listOfFiles = new File(workingDir.concat("/request")).listFiles();
		
		for(int i=0; i < listOfFiles.length; i++){
			
			if(listOfFiles[i].isFile()){
				String name = listOfFiles[i].getName();
				String reqName = "request/".concat(name);
				solve(reqName, name);
			}
		}
	}
	@SuppressWarnings("unused")
	public void solve(String reqName, String name){
		
		//list of arguments and the command to execute the solver  
				
				String[] cmdList = {"solver/SS", reqName };
				
				ProcessBuilder pb = new ProcessBuilder(cmdList);
				
				try{
					
					 pb.directory(new File(workingDir));
					 String resultFolder = workingDir.concat("/result");
					
					 String logFile = name+"_log.txt";
					
					//File log = new File(workingDir.concat("/result/".concat(logFile)));
					 File log = new File(resultFolder, logFile);
					 File error = new File(resultFolder, "error");
					
					 pb.redirectError(Redirect.to(error));
					 pb.redirectOutput(Redirect.to(log));
					 
					 Process p = pb.start();
					 
				}catch(IOException e){
					e.printStackTrace();
				}
				}
				
			}


