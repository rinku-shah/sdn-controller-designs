package org.onosproject.p4tutorial.epc;

import java.io.BufferedReader;
import java.io.File;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.UnsupportedEncodingException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collection;
import java.util.Collections;
import java.util.Date;
import java.util.HashMap;
import java.util.Hashtable;
import java.util.Iterator;
import java.util.List;
import java.util.Map;
import java.util.Set;
import java.util.concurrent.ConcurrentHashMap;
import org.slf4j.Logger;
import static org.slf4j.LoggerFactory.getLogger;

/*import net.floodlightcontroller.core.FloodlightContext;
import net.floodlightcontroller.core.IFloodlightProviderService;
import net.floodlightcontroller.core.IOFMessageListener;
import net.floodlightcontroller.core.IOFSwitch;
import net.floodlightcontroller.core.IOFSwitchListener;
import net.floodlightcontroller.core.PortChangeType;
import net.floodlightcontroller.core.IListener.Command;
import net.floodlightcontroller.core.internal.FloodlightProvider;
import net.floodlightcontroller.core.internal.IOFSwitchService;
import net.floodlightcontroller.core.module.FloodlightModuleContext;
import net.floodlightcontroller.core.module.FloodlightModuleException;
import net.floodlightcontroller.core.module.IFloodlightModule;
import net.floodlightcontroller.core.module.IFloodlightService;
import net.floodlightcontroller.core.util.SingletonTask;
import net.floodlightcontroller.packet.Data;
import net.floodlightcontroller.packet.Ethernet;
import net.floodlightcontroller.packet.IPv4;
import net.floodlightcontroller.packet.PacketParsingException;
import net.floodlightcontroller.packet.UDP;
import net.floodlightcontroller.threadpool.IThreadPoolService;

import org.projectfloodlight.openflow.protocol.OFFactories;
import org.projectfloodlight.openflow.protocol.OFFlowMod;
import org.projectfloodlight.openflow.protocol.OFMessage;
import org.projectfloodlight.openflow.protocol.OFPacketIn;
import org.projectfloodlight.openflow.protocol.OFPacketOut;
import org.projectfloodlight.openflow.protocol.OFPortDesc;
import org.projectfloodlight.openflow.protocol.OFStatsReply;
import org.projectfloodlight.openflow.protocol.OFStatsType;
import org.projectfloodlight.openflow.protocol.OFType;
import org.projectfloodlight.openflow.protocol.OFVersion;
import org.projectfloodlight.openflow.protocol.action.OFAction;
import org.projectfloodlight.openflow.protocol.action.OFActionNicira;
import org.projectfloodlight.openflow.protocol.action.OFActionNiciraController;
import org.projectfloodlight.openflow.protocol.action.OFActionNiciraController.Builder;
import org.projectfloodlight.openflow.protocol.action.OFActionNiciraDecTtl;
import org.projectfloodlight.openflow.protocol.action.OFActionOutput;
import org.projectfloodlight.openflow.protocol.action.OFActionSetNwDst;
import org.projectfloodlight.openflow.protocol.match.Match;
import org.projectfloodlight.openflow.protocol.match.MatchField;
import org.projectfloodlight.openflow.types.DatapathId;
import org.projectfloodlight.openflow.types.EthType;
import org.projectfloodlight.openflow.types.IPv4Address;
import org.projectfloodlight.openflow.types.IpDscp;
import org.projectfloodlight.openflow.types.IpProtocol;
import org.projectfloodlight.openflow.types.MacAddress;
import org.projectfloodlight.openflow.types.OFBufferId;
import org.projectfloodlight.openflow.types.OFPort;
import org.projectfloodlight.openflow.types.OFVlanVidMatch;
import org.projectfloodlight.openflow.types.TransportPort;
import org.projectfloodlight.openflow.types.VlanVid;
import org.sdnplatform.sync.IStoreListener;
import org.sdnplatform.sync.internal.rpc.IRPCListener;
import org.sdnplatform.sync.internal.SyncManager;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;*/

public class OnlineDesignAdaptation {
	    String controllerIdStr;
	    		
		public OnlineDesignAdaptation(){
			OnlineThread t;
			t = new OnlineThread();
			t.start();
		}
		
}

class OnlineThread implements Runnable {
	private static final Logger log = getLogger(EpcApp.class);
	//private static IOFSwitch sw1,sw2,sw3,sw4,sw5,sw6;
	public InterControllerClient clt1, clt2, clt3, clt4, clt5, clt6; //clients for SGW conn
	//public InterControllerClient dclt1, dclt2, dclt3, dclt4, dclt5, dclt6; //clients for DGW conn
	public InterControllerServer server;
	public Boolean flag2 = false;
	
	public OnlineThread() {
	}

	public void start() {
		// TODO Auto-generated method stub
		log.warn("Online Thread started");
		initServer();
	}
	
	private void initServer(){
		try {
			server=new InterControllerServer(this,Integer.parseInt(Constants.LOCAL_1_PORT));
		} catch (NumberFormatException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		sendPacketToLocal("Hello... U R Connected To ROOT");
		//sendPacketToSwitch("Hello... U R Connected To ROOT");

	}
		
	public void sendPacketToLocal(String msg){  //Sending first packet 
		try {
			sendPacketToController("", msg);
		} catch (NumberFormatException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		} catch (IOException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}
	}

	public void sendPacket(String dgw_dpId, String msg){ //Sending packet to specific controller
		String receiverIP = "";
		//String sgw_dpId = Constants.getSgwDpid(dgw_dpId);
		//DeviceId sgwswitchName = Constants.getSgwswitchName(dgw_dpId);
		receiverIP = Constants.getSgwIp(dgw_dpId);

		try {
			sendPacketToController(receiverIP, msg);
		} catch (NumberFormatException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		} catch (IOException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}
	}
	
	
	@Override
	public void run() {
		log.warn("Entered Online Run");
			
	}
	
	//incoming packet from root
	//msg=dgw_dpId @@ PUT/DEL @@ map_name @@ key @@ value ; @@ : Constants.STOREKEYSEPARATOR
	//maps: "uekey_sgwteid_map" "uekey_uestate_map" "uekey_guti_map" 
	public void processControllerPacket(String msg){
		String tmpArray[];
		tmpArray = msg.split(Constants.STOREKEYSEPARATOR);
		//0:dgw_dpId, 1:PUT/DEL, 2:mapName, 3:key, 4:value		
		StringBuilder response;	
			
		switch(tmpArray[1]){
		case "PUT":
		//public static void put(int msgId,String dgwDpId, String mapName, String key, String val) 
		//fake msg-id=1
			FT.put(1, tmpArray[0], tmpArray[2], tmpArray[3], tmpArray[4]);
			break;
		
		case "DEL":
			//public static void del(int msgId,String dgwDpId,String mapName, String key)
			FT.del(1, tmpArray[0], tmpArray[2], tmpArray[3]);
			//FT.put(1, tmpArray[0], tmpArray[2], tmpArray[3], tmpArray[4]);
			break;
		default:
			log.warn("Received message: {}", msg);
		}
	}
	
	public boolean sendPacketToController(String receiverIP, String data) throws NumberFormatException, IOException{
		if(!flag2){
			flag2 = true;
			clt1=new InterControllerClient(Constants.SGW_IP_1,Integer.parseInt(Constants.ROOT_PORT));
			clt2=new InterControllerClient(Constants.SGW_IP_2,Integer.parseInt(Constants.ROOT_PORT));
			clt3=new InterControllerClient(Constants.SGW_IP_3,Integer.parseInt(Constants.ROOT_PORT));
			clt4=new InterControllerClient(Constants.SGW_IP_4,Integer.parseInt(Constants.ROOT_PORT));
			//clt5=new InterControllerClient(Constants.SGW_IP_5,Integer.parseInt(Constants.LOCAL_5_PORT));
			//clt6=new InterControllerClient(Constants.SGW_IP_6,Integer.parseInt(Constants.LOCAL_6_PORT));
		}

		switch(receiverIP){
			case Constants.SGW_IP_1:
				clt1.clientSend(data);
				break;
			case Constants.SGW_IP_2:
				clt2.clientSend(data);
				break;
			case Constants.SGW_IP_3:
				clt3.clientSend(data);
				break;
			case Constants.SGW_IP_4:
				clt4.clientSend(data);
				break;
			default:
				log.warn("NO SGW MATCH FOUND");
		}
		if(Constants.DEBUG){
			log.warn("sent: {}", data);
		}
		return true;
	}

}
