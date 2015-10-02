package net.floodlightcontroller.solver;

import java.util.ArrayList;
import java.util.Collection;
import java.util.Map;

import org.projectfloodlight.openflow.protocol.OFMessage;
import org.projectfloodlight.openflow.protocol.OFType;

import net.floodlightcontroller.core.FloodlightContext;
import net.floodlightcontroller.core.IFloodlightProviderService;
import net.floodlightcontroller.core.IOFMessageListener;
import net.floodlightcontroller.core.IOFSwitch;
import net.floodlightcontroller.core.module.FloodlightModuleContext;
import net.floodlightcontroller.core.module.FloodlightModuleException;
import net.floodlightcontroller.core.module.IFloodlightModule;
import net.floodlightcontroller.core.module.IFloodlightService;
import net.floodlightcontroller.packet.Ethernet;

public class Graph implements IFloodlightModule, IOFMessageListener {
	public Graph(){
		main(null);
	}
	protected IFloodlightProviderService floodlightProvider;
		
		private int numDC;
		private int numVF;
		private ArrayList<Node> dC;
		private ArrayList<VirtualFunction> vF;
		private Link topology[][];
		private Map<String, ArrayList<VFConfig>> symbolTable;
		private static double[][] latency;
		public Graph(int nodes){
			this.numDC = nodes;
			this.topology = new Link[numDC][numDC];
			
		}
		
		@SuppressWarnings("unused")
		public void addEdge(double[][] latency){
			
			Link[] edge = new Link[latency[0].length*latency.length];
			for(int i=0; i < latency.length; i++){
				for(int j=0; j < latency.length; j++){
					this.topology[i][j] = new Link(i,j,latency[i][j]);
				}
			}
			
		}
		
		
		public int getNumDC() {
			return numDC;
		}

		public void setNumDC(int numDC) {
			this.numDC = numDC;
		}

		public int getNumVF() {
			return numVF;
		}

		public void setNumVF(int numVF) {
			this.numVF = numVF;
		}

		public ArrayList<Node> getdC() {
			return dC;
		}

		public void setdC(ArrayList<Node> dC) {
			this.dC = dC;
		}

		public ArrayList<VirtualFunction> getvF() {
			return vF;
		}

		public void setvF(ArrayList<VirtualFunction> vF) {
			this.vF = vF;
		}

		public Link[][] getTopology() {
			return topology;
		}

		public void setTopology(Link[][] topology) {
			this.topology = topology;
		}

		public Map<String, ArrayList<VFConfig>> getSymbolTable() {
			return symbolTable;
		}

		public void setSymbolTable(Map<String, ArrayList<VFConfig>> symbolTable) {
			this.symbolTable = symbolTable;
		}

		public double[][] getLatency() {
			return latency;
		}

		public void setLatency(double[][] latency) {
			Graph.latency = latency;
		}

		@SuppressWarnings({ "static-access", "unused" })
		public static void main(String args[]){
			System.out.println("Starting....");
			Graph g = new Graph(11);
			
			g.dC = Node.addNodes();
			g.vF = VirtualFunction.addVf(8);
			
			Data initializer = new Data();
			g.latency=initializer.setLatency();
			g.addEdge(latency);
			g.symbolTable=initializer.mapVFToDC();
			
			//generate the request files
			RequestGenerator reqGen= new RequestGenerator(g);
			
			//solve
			Solver s = new Solver();
			Statistics stat = new Statistics();
		}

		@Override
		public String getName() {
			// TODO Auto-generated method stub
			 return Graph.class.getSimpleName();
		}

		@Override
		public boolean isCallbackOrderingPrereq(OFType type, String name) {
			// TODO Auto-generated method stub
			return false;
		}

		@Override
		public boolean isCallbackOrderingPostreq(OFType type, String name) {
			// TODO Auto-generated method stub
			return false;
		}

		@Override
		public net.floodlightcontroller.core.IListener.Command receive(IOFSwitch sw, OFMessage msg,
				FloodlightContext cntx) {
			 Ethernet eth =
		                IFloodlightProviderService.bcStore.get(cntx,
		                                            IFloodlightProviderService.CONTEXT_PI_PAYLOAD);
			 return Command.CONTINUE;
		}

		@Override
		public Collection<Class<? extends IFloodlightService>> getModuleServices() {
			// TODO Auto-generated method stub
			return null;
		}

		@Override
		public Map<Class<? extends IFloodlightService>, IFloodlightService> getServiceImpls() {
			// TODO Auto-generated method stub
			return null;
		}

		@Override
		public Collection<Class<? extends IFloodlightService>> getModuleDependencies() {
			  Collection<Class<? extends IFloodlightService>> l =
			          new ArrayList<Class<? extends IFloodlightService>>();
			          l.add(IFloodlightProviderService.class);
			          return l;
		}

		@Override
		public void init(FloodlightModuleContext context) throws FloodlightModuleException {
		    floodlightProvider = context.getServiceImpl(IFloodlightProviderService.class);
			
		}

		@Override
		public void startUp(FloodlightModuleContext context) throws FloodlightModuleException {
			 floodlightProvider.addOFMessageListener(OFType.PACKET_IN, this);
			
		}
		
		
	}
		

