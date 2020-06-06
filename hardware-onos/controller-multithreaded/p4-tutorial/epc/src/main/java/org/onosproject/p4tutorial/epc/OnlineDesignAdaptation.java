package org.onosproject.p4tutorial.epc;

import org.onlab.packet.Ethernet;
import org.onlab.packet.IPacket;
import org.onlab.packet.UDP;
import org.onlab.packet.IPv4;
import org.onlab.packet.Ip4Prefix;
import org.onlab.packet.IpPrefix;

import org.onlab.packet.Ip4Address;
import org.onlab.packet.TCP;
import org.onlab.packet.TpPort;
import org.onlab.packet.UDP;
import org.onlab.packet.MacAddress;
import com.google.common.collect.Lists;
import org.apache.felix.scr.annotations.Activate;
import org.apache.felix.scr.annotations.Component;
import org.apache.felix.scr.annotations.Deactivate;
import org.apache.felix.scr.annotations.Reference;
import org.apache.felix.scr.annotations.ReferenceCardinality;
import org.apache.felix.scr.annotations.Service;
import org.onlab.packet.IpAddress;
import org.onosproject.core.ApplicationId;
import org.onosproject.core.CoreService;
import org.onosproject.net.DeviceId;
import org.onosproject.net.Host;
import org.onosproject.net.Link;
import org.onosproject.net.Path;
import org.onosproject.net.PortNumber;
import org.onosproject.net.flow.DefaultFlowRule;
import org.onosproject.net.flow.DefaultTrafficSelector;
import org.onosproject.net.flow.DefaultTrafficTreatment;
import org.onosproject.net.flow.FlowRule;
import org.onosproject.net.HostId;
import org.onosproject.net.flow.FlowRuleService;
import org.onosproject.net.flow.criteria.PiCriterion;
import org.onosproject.net.host.HostEvent;
import org.onosproject.net.host.HostListener;
import org.onosproject.net.host.HostService;
import org.onosproject.net.packet.InboundPacket;
import org.onosproject.net.packet.PacketContext;
import org.onosproject.net.packet.PacketPriority;
import org.onosproject.net.packet.PacketProcessor;
import org.onosproject.net.packet.PacketService;
import org.onosproject.net.pi.model.PiActionId;
import org.onosproject.net.pi.model.PiActionParamId;
import org.onosproject.net.pi.model.PiMatchFieldId;
import org.onosproject.net.pi.model.PiTableId;
import org.onosproject.net.pi.runtime.PiAction;
import org.onosproject.net.pi.runtime.PiActionParam;
import org.onosproject.net.topology.Topology;
import org.onosproject.net.topology.TopologyService;
import org.onosproject.net.flow.TrafficSelector;
import org.onosproject.net.ConnectPoint;
import org.onlab.packet.Data;
import org.onosproject.net.packet.DefaultOutboundPacket;
import org.onosproject.net.packet.OutboundPacket;
import org.onosproject.net.packet.PacketService;
import org.onosproject.net.flow.DefaultTrafficTreatment;
import org.onosproject.net.flow.TrafficTreatment;

//import org.slf4j.Logger;

import java.util.Collections;
import java.util.List;
import java.util.Random;
import java.util.Set;
import java.nio.ByteBuffer;
import java.util.Arrays;
import java.nio.charset.Charset;
import java.util.concurrent.atomic.AtomicInteger;
import java.nio.charset.StandardCharsets;
import java.io.IOException;
import java.io.UnsupportedEncodingException;
import java.util.ArrayList;
import java.util.Collection;
import java.util.Date;
import java.util.HashMap;
import java.util.Hashtable;
import java.util.List;
import java.util.Map;
import java.util.Set;
import java.util.concurrent.ConcurrentHashMap;

//import static org.slf4j.LoggerFactory.getLogger;

import java.io.BufferedReader;
import java.io.File;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.Collection;
import java.util.Date;
import java.util.HashMap;
import java.util.Hashtable;
import java.util.Iterator;
//import java.util.List;
//import java.util.Map;
//import java.util.Set;
//import java.util.concurrent.ConcurrentHashMap;
import org.slf4j.Logger;
import static org.slf4j.LoggerFactory.getLogger;

public class OnlineDesignAdaptation {
	    	OnlineThread t;	
		ApplicationId appId;
		public OnlineDesignAdaptation(ApplicationId id){
			//OnlineThread t;
			appId = id;
			t = new OnlineThread(id);
			t.start();
		}

		public void sendPacketRemote(String dgw_dpId, String msg){ //Sending packet to specific controller
			t.sendPacket(dgw_dpId, msg);
		}
         
		
}

class OnlineThread implements Runnable {
	//private static IOFSwitch sw1,sw2,sw3,sw4,sw5,sw6;
	private static final Logger log = getLogger(EpcApp.class);
	public InterControllerClient[] clt = new InterControllerClient[200];
	public InterControllerClient clt1, clt2, clt3, clt4, clt5, clt6; //clients for SGW conn
	//public InterControllerClient dclt1, dclt2, dclt3, dclt4, dclt5, dclt6; //clients for DGW conn
	public InterControllerServer server, server1, server2, server3;
	public Boolean flag2 = false;
        
        private FlowRuleService flowRuleService;	
        private ConcurrentHashMap<String, String> imsi_xres_mapping = new ConcurrentHashMap<String, String>();
        private ConcurrentHashMap<String, String> uekey_guti_map = new ConcurrentHashMap<String, String>(); // Key: UE_Key, Value: GUTI
        private ConcurrentHashMap<String, String[]> uekey_nas_keys_map = new ConcurrentHashMap<String, String[]>(); // Key = IMSI, Value = [0]: K_ASME, [1]: NAS Integrity key, NAS Encryption key
	HSS hss = new HSS();
        SGW sgw = new SGW();
        FT ft = new FT();
        public ApplicationId appId;
	public OnlineThread(ApplicationId id) {
		appId = id;
		try{
                        for (int j=0; j<200; j++){
                                int port = 2101 + j;
                                //clt[j]=new InterControllerClient(Constants.RAN_IP,2101);
                                clt[j] = new InterControllerClient(Constants.RAN_IP,port);
                        }
                        log.info("Started UDP clients");
		} catch (IOException e1) {
                        e1.printStackTrace();
                }

	}

	public void start() {
		// TODO Auto-generated method stub
		log.warn("Online Thread started");
		initServer();
	}
	
	private void initServer(){
		try {
			server=new InterControllerServer(this,Integer.parseInt(Constants.UDP_PORT));
			log.info("Started UDP server on port {}", Constants.UDP_PORT);
			server1=new InterControllerServer(this,Integer.parseInt(Constants.UDP_PORT_1));
                        log.info("Started UDP server on port {}", Constants.UDP_PORT_1);
			server2=new InterControllerServer(this,Integer.parseInt(Constants.UDP_PORT_2));
                        log.info("Started UDP server on port {}", Constants.UDP_PORT_2);
			server3=new InterControllerServer(this,Integer.parseInt(Constants.UDP_PORT_3));
                        log.info("Started UDP server on port {}", Constants.UDP_PORT_3);
			/*InterControllerClient[] clt = new InterControllerClient[100];
			
		        for (int j=0; j<100; j++){
                                int port = 2101 + j;
                                //clt[j]=new InterControllerClient(Constants.RAN_IP,2101);
                                clt[j] = new InterControllerClient(Constants.RAN_IP,port);
                        }
                        log.info("Started UDP clients");*/

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
	
	private String[] receiveDecryptedArray(String tmpArray[]){
            //tmpArray[1] => Encrypted text, tmpArray[2] => HMAC, tmpArray[3] => IMSI
            Utils.hmacDigest(tmpArray[1], Constants.SAMPLE_ENC_KEY);
            String decText = "";
            Utils.aesEncrypt(tmpArray[1], Constants.SAMPLE_ENC_KEY);
            return decText.split(Constants.SEPARATOR);
        }
	
	private String[] KDF_NAS(String K_ASME, int NAS_integrity_algo_id, int NAS_cipher_algo_id){
            String NAS_keys[] = new String[2];  // NAS_keys[0]: Integrity key K_NAS_int, NAS_keys[1]: Encryption key K_NAS_enc
            /*long K_NAS_int = K_ASME * 2 + NAS_integrity_algo_id;
            long K_NAS_enc = K_ASME * 4 + NAS_cipher_algo_id;*/
            long K_NAS_int = 2 * 2 + NAS_integrity_algo_id;
            long K_NAS_enc = 2 * 4 + NAS_cipher_algo_id;
            NAS_keys[0] = K_NAS_int + "";
            NAS_keys[1] = K_NAS_enc + "";

            if(NAS_keys[1].length() > Constants.ENC_KEY_LENGTH){
                NAS_keys[1].substring(0, Constants.ENC_KEY_LENGTH);
            }
            else if(NAS_keys[1].length() < Constants.ENC_KEY_LENGTH){
                NAS_keys[1] += Constants.SAMPLE_ENC_KEY.substring(0, Constants.ENC_KEY_LENGTH - NAS_keys[1].length());
            }
            return NAS_keys;
        }
	
	public void sendPacketToLocal(String msg){  //Sending first packet 
		try {
			sendPacketToController("", msg, 101);
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
			sendPacketToController(receiverIP, msg, 101);
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
	
	public boolean sendPacketToController(String receiverIP, String data, int ue_num) throws NumberFormatException, IOException{
		//if(!flag2){
		//	flag2 = true;
			/*clt1=new InterControllerClient(Constants.SGW_IP_1,Integer.parseInt(Constants.LOCAL_1_PORT));
			clt2=new InterControllerClient(Constants.SGW_IP_2,Integer.parseInt(Constants.LOCAL_2_PORT));
			clt3=new InterControllerClient(Constants.SGW_IP_3,Integer.parseInt(Constants.LOCAL_3_PORT));
			clt4=new InterControllerClient(Constants.SGW_IP_4,Integer.parseInt(Constants.LOCAL_4_PORT));*/
			//clt5=new InterControllerClient(Constants.SGW_IP_5,Integer.parseInt(Constants.LOCAL_5_PORT));
			//clt6=new InterControllerClient(Constants.SGW_IP_6,Integer.parseInt(Constants.LOCAL_6_PORT));
			/*for (int j=0; j<100; j++){
				int port = 2101 + j;
				i//clt[j]=new InterControllerClient(Constants.RAN_IP,2101);
				clt[j]=new InterControllerClient(Constants.RAN_IP,port);
			}*/
	//	}
		//int port = ue_num + 2000;
		int index = 0;
		/*if(ue_num < 151)
			index = ue_num - Constants.START_UE_1; //index from 0 to 49
		else if((ue_num >= 151) && (ue_num < 201)) 
			index = ue_num - Constants.START_UE_2 + 50; //index from 50 to 99
		else if((ue_num >= 201) && (ue_num < 251))
                        index = ue_num - Constants.START_UE_3 + 100; //index from 100 to 149
		else if((ue_num >= 251) && (ue_num < 301))
                        index = ue_num - Constants.START_UE_4 + 150; //index from 150 to 199*/
		if(ue_num < 126)
                        index = ue_num - Constants.START_UE_1; //index from 0 to 24
                else if((ue_num >= 126) && (ue_num < 151))
                        index = ue_num - Constants.START_UE_2 + 25; //index from 25 to 49
                else if((ue_num >= 151) && (ue_num < 176))
                        index = ue_num - Constants.START_UE_3 + 50; //index from 50 to 74
                else if((ue_num >= 176) && (ue_num < 201))
                        index = ue_num - Constants.START_UE_4 + 75; //index from 75 to 99
		if(Constants.DEBUG)
			log.info("send socket index = {} for ue_num= {}", index, ue_num);

		clt[index].clientSend(data);
		/*switch(receiverIP){
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
		}*/
		if(Constants.DEBUG){
			log.warn("sent: {}", data);
		}
		return true;
	}

	//incoming packet from root
	//msg=dgw_dpId @@ PUT/DEL @@ map_name @@ key @@ value ; @@ : Constants.STOREKEYSEPARATOR
	//maps: "uekey_sgwteid_map" "uekey_uestate_map" "uekey_guti_map" 
	public void processControllerPacket(byte[] msg, String result) {   //String msg){
	//private ConcurrentHashMap<String, String> imsi_xres_mapping = new ConcurrentHashMap<String, String>();
        //private ConcurrentHashMap<String, String> uekey_guti_map = new ConcurrentHashMap<String, String>(); // Key: UE_Key, Value: GUTI
        //private ConcurrentHashMap<String, String[]> uekey_nas_keys_map = new ConcurrentHashMap<String, String[]>(); // Key = IMSI, Value = [0]: K_ASME, [1]: NAS Integrity key, NAS Encryption key
        //HSS hss = new HSS();
        //SGW sgw = new SGW();
        //FT ft = new FT();
        //FR fr = new FR();
		int uePort = Constants.DEFAULT_SWITCH_UE_PORT;
		String payload;
		
		byte[] p = msg;
		//byte[] p = result.getBytes();
		//log.info("Received data: {}", result);
		byte [] b1 = Arrays.copyOfRange(p, 0, 1); //code
		byte [] b2 = Arrays.copyOfRange(p, 1, 7); //sep1

		byte code = ByteBuffer.wrap(b1).get();
		int type = code;
		String sep1 = new String(b2, StandardCharsets.UTF_8); //6 byte
				
		payload = new String(p,  Charset.forName("UTF-8"));

		if(Constants.DEBUG){
			log.info("received payload = {} code = {} ", payload, type);
		}

		String tmpArray[], tmpArray2[], decArray[], NAS_Keys[];
		String NAS_MAC = null;
		// String res, xres, autn, rand, K_ASME, imsi, ue_nw_capability, KSI_ASME, SQN, tai;
		String res, xres, autn, rand, K_ASME,imsi, KSI_ASME, SQN,tai;
		byte ue_nw_capability;
		StringBuilder response;

		/************************************************************************************/

		if(payload.contains(Constants.SEPARATOR)){
			tmpArray = payload.split(Constants.SEPARATOR);
	
			if(Constants.DEBUG) {
				log.warn("tmpArray[0] = {}", tmpArray[0]);
			}
			//String type = tmpArray[0];
			// switch(tmpArray[0]){
			switch(Integer.toString(type)){
				
				case Constants.REQUEST_STARTING_IP:
					if(Constants.DEBUG){
//                      System.out.println("Inside case REQUEST_STARTING_IP");
						log.warn("Inside case REQUEST_STARTING_IP");
						log.warn("Request Starting IP address from PGW via SGW");
					}
					/*String deviceID = (String)connectPoint.deviceId().toString();  //hardcoding
					String sw[]= deviceID.split(":");
					String swName = sw[2];
					*/
					/***************get starting UE IP  **************************************/

					//String ip = sgw.getStartingIPAddress(swName);
					String ip = sgw.getStartingIPAddress("1");

					response = new StringBuilder();
					response.append(Constants.SEND_STARTING_IP).append(Constants.SEPARATOR).append(ip);

					if(Constants.DEBUG){
						log.warn("Starting IP= {}",ip);
						log.warn("Response to send = {}",response);
					}

					//build_response_pkt(connectPoint,srcMac,dstMac,ipv4Protocol,ipv4SourceAddress,udp_dstport,udp_srcport,response.toString());
					try {
						sendPacketToController(Constants.RAN_IP, response.toString(), 101);
					} catch (NumberFormatException e1) {
                		        	e1.printStackTrace();
			                	} catch (IOException e1) {
		                        		e1.printStackTrace();
                				}

					response = null;
					
					break;

				case Constants.AUTHENTICATION_STEP_ONE:
					if(Constants.DEBUG){
						log.info("Inside case AUTHENTICATION_STEP_ONE");
					}

					/************************* Validating user in HSS*********************************/
						byte [] b3 =Arrays.copyOfRange(p, 7, 11); //imsi
						byte [] b4 = Arrays.copyOfRange(p, 11, 17); //sep2
						byte [] b5 = Arrays.copyOfRange(p, 17, 18); //ue_nw_cap
						byte [] b6 =Arrays.copyOfRange(p, 18, 24); //sep3
						byte [] b7 = Arrays.copyOfRange(p, 24, 56); //ksi_asme //32 byte
						byte [] b8 = Arrays.copyOfRange(p, 56, 62); //sep4
						byte [] b9 = Arrays.copyOfRange(p, 62, 66); //sqn
						byte [] b10 = Arrays.copyOfRange(p, 66, 72); //sep5
						byte [] b11 = Arrays.copyOfRange(p, 72, 80); //tai
	
						/*byte code = ByteBuffer.wrap(b1).get();
						System.out.println("code = " + code);*/

	
						int imsi1 = ByteBuffer.wrap(b3).getInt();
						imsi = Integer.toString(imsi1);
	
						String sep2 = new String(b4, StandardCharsets.UTF_8); //6 byte
	
						ue_nw_capability = ByteBuffer.wrap(b5).get();
	
						String sep3 = new String(b6, StandardCharsets.UTF_8); //6 byte
	
						int ksi_asme = ByteBuffer.wrap(b7).getInt();
						KSI_ASME = Integer.toString(ksi_asme);
	
						String sep4 = new String(b8, StandardCharsets.UTF_8); //6 byte
	
						int sqn = ByteBuffer.wrap(b9).getInt();
						SQN = Integer.toString(sqn);
	
						String sep5 = new String(b10, StandardCharsets.UTF_8); //6 byte
	
						Long tai1 = ByteBuffer.wrap(b11).getLong();
						tai = Long.toString(tai1);

						if(Constants.BITWISE_DEBUG){
						log.info("Inside case AUTHENTICATION_STEP_ONE");
							log.warn("imsi = {}" , imsi1);
							log.warn("sep2 = {}" , sep2);
							log.warn("ue_nw_cap = {}" , ue_nw_capability);
							log.warn("sep3 = {}" , sep3);
							log.warn("ksi_asme = {}", ksi_asme);
							log.warn("sep4 = {}" ,sep4);
							log.warn("sqn = {}" , sqn);
							log.warn("sep5 = {}", sep5);
							log.warn("tai = {}" , tai1);
						}
	
					// imsi = tmpArray[1];
					// ue_nw_capability = tmpArray[2];
					// KSI_ASME = tmpArray[3];
					// SQN = tmpArray[4];	// UE sequence number
					// tai = tmpArray[5];	// Tracking area ID
					//Date d3 = new Date();

					int[][][] roundKeys= new int[11][4][4];
					auc_vector_t av = hss.validateUser(imsi, Constants.SN_ID, Constants.NW_TYPE, SQN, tai, roundKeys);
					// payload = hss.validateUser(imsi, Constants.SN_ID, Constants.NW_TYPE, Integer.parseInt(SQN), tai);
					//if(Constants.DEBUG){
					//	Date d4 = new Date();
					//	timeDiff(d3, d4, 11);
					//}
					/*if(payload != null && payload.contains(Constants.SEPARATOR)){
							tmpArray2 = payload.split(Constants.SEPARATOR);
							// tmpArray2[0]: xres, tmpArray2[1]: autn, tmpArray2[2]: rand, tmpArray2[3]: K_ASME
							xres = tmpArray2[0];
							autn = tmpArray2[1];
							rand = tmpArray2[2];
							K_ASME = tmpArray2[3];*/
						
							/*xres = av.xres;
							autn = av.autn;
							rand = av.rand;
							K_ASME = av.kasme;*/
						if(Constants.DEBUG){
							log.warn("INITIAL imsi= {} and  msisdn= {}",imsi,ue_nw_capability);
							// System.out.println("INITIAL imsi="+imsi+" msisdn="+ ue_nw_capability);
						}
						//////////////////////////////////////EDIT//////////////////
						StringBuilder xresS = new StringBuilder();
						StringBuilder K_ASMES = new StringBuilder();
						for(int k=0; k<8; k++){
							if(k!=7)
								xresS.append(av.xres[k]);//.append(Constants.INTSEPARATOR);
							else 
								xresS.append(av.xres[k]);
						}
						for(int k=0; k<32; k++){
							if(k!=31)
								K_ASMES.append(av.kasme[k]);//.append(Constants.INTSEPARATOR);
							else 
								K_ASMES.append(av.kasme[k]);
						}
						imsi_xres_mapping.put(imsi, xresS.toString());
						uekey_nas_keys_map.put(imsi, new String[]{K_ASMES.toString(), "", ""});
						//////////////////////////////////////EDIT//////////////////
						KSI_ASME = "1";
						//System.out.println("Rand="+rand+" AUTN="+autn+" K_ASME="+K_ASME);
						response = new StringBuilder();
						/*response.append(Constants.AUTHENTICATION_STEP_TWO).append(Constants.SEPARATOR).append(strTohex(rand, 16)).append(Constants.SEPARATOR);
						response.append(strTohex(autn, 16));
						response.append(Constants.SEPARATOR).append(strTohex(K_ASME,32));*/
						
						/*StringBuilder randS = new StringBuilder();
						System.out.print("RAND INT ARRAY: ");
						for(int j=0; j<16;j++){
							randS.append(rand[j]).append(Constants.SEPARATOR);
						}
						System.out.println(randS);*/
						StringBuilder randS = new StringBuilder();
						for(int j=0; j<16;j++){
							if(j !=15){
								randS.append(av.rand[j]).append(Constants.INTSEPARATOR);
							}else{
								randS.append(av.rand[j]);
							}
						}
						//System.out.println("randS= "+ randS);
						StringBuilder autnS = new StringBuilder();
						for(int j=0; j<16;j++){
							if(j !=15){
								autnS.append(av.autn[j]).append(Constants.INTSEPARATOR);
							}else{
								autnS.append(av.autn[j]);
							}
						}
						//System.out.println("autnS= "+ autnS);
						/*response.append(Constants.AUTHENTICATION_STEP_TWO).append(Constants.SEPARATOR).append(rand.toString()).append(Constants.SEPARATOR);
						response.append(autn.toString());
						response.append(Constants.SEPARATOR).append(K_ASME.toString());*/
						
						response.append(Constants.AUTHENTICATION_STEP_TWO).append(Constants.SEPARATOR).append(randS).append(Constants.SEPARATOR);
						response.append(autnS);
						response.append(Constants.SEPARATOR).append(KSI_ASME); //K_ASME
						
						if(Constants.DEBUG){
							log.warn("response= {}",response.toString());
						}
						/*response = new StringBuilder();
						response.append(Constants.AUTHENTICATION_STEP_TWO).append(Constants.SEPARATOR).append("1234").append(Constants.SEPARATOR);
						response.append("1234");
						response.append(Constants.SEPARATOR).append("1");*/
						// sendPacket(sw, inPort, destMac, sourceMac, dstIp, srcIp, IpProtocol.UDP, dstPort, srcPort, response.toString());
						//build_response_pkt(connectPoint,srcMac,dstMac,ipv4Protocol,ipv4SourceAddress,udp_dstport,udp_srcport,response.toString());
						try {
							sendPacketToController(Constants.RAN_IP, response.toString(),(imsi1/1000));
						} catch (NumberFormatException e1) {
                                                e1.printStackTrace();
                                                } catch (IOException e1) {
                                                        e1.printStackTrace();
                                                }

						response = null;
					/*}else{
						System.out.println("ERROR:: STEP ONE AUTHENTICATION failure with imsi="+imsi+" and msisdn="+ue_nw_capability+" temp="+payload);
						sendPacket(sw, inPort, destMac, sourceMac, dstIp, srcIp,  IpProtocol.UDP, dstPort, srcPort, Constants.AUTHENTICATION_FAILURE);
						//System.exit(1);
					}*/
					
													//                         if(Constants.DEBUG){
													//                             log.warn("got payload from HSS = {}",payload);
													//                             Date d4 = new Date();
													//                             timeDiff(d3, d4, 11);
													//                         }

													//                         if(payload != null && payload.contains(Constants.SEPARATOR)){
													//                             tmpArray2 = payload.split(Constants.SEPARATOR);
													//                             // tmpArray2[0]: xres, tmpArray2[1]: autn, tmpArray2[2]: rand, tmpArray2[3]: K_ASME
													//                             xres = tmpArray2[0];
													//                             autn = tmpArray2[1];
													//                             rand = tmpArray2[2];
													//                             K_ASME = tmpArray2[3];
													//                             if(Constants.DEBUG){
													//                                 log.warn("INITIAL imsi = {}",imsi);
													//                                 log.warn(" msisdn = {}", ue_nw_capability);
													//                             }
													//                             imsi_xres_mapping.put(imsi, xres);
													//                             uekey_nas_keys_map.put(imsi, new String[]{K_ASME, "", ""});
													//                             KSI_ASME = "1";
													//                             response = new StringBuilder();
													//                             response.append(Constants.AUTHENTICATION_STEP_TWO).append(Constants.SEPARATOR).append(rand).append(Constants.SEPARATOR);
													//                             response.append(autn);
													//                             response.append(Constants.SEPARATOR).append(KSI_ASME);
													// //                            sendPacket(sw, inPort, destMac, sourceMac, dstIp, srcIp, IpProtocol.UDP, dstPort, srcPort, response.toString());
													//                             build_response_pkt(connectPoint,srcMac,dstMac,ipv4Protocol,ipv4SourceAddress,udp_dstport,udp_srcport,response.toString());
													//                             response = null;
													//                         }else{
													//                             log.warn("ERROR:: STEP ONE AUTHENTICATION failure with imsi={}",imsi);
													//                             log.warn(" and msisdn={}",ue_nw_capability);
													//                             log.warn(" temp = {}",payload);
													// //                            sendPacket(sw, inPort, destMac, sourceMac, dstIp, srcIp,  IpProtocol.UDP, dstPort, srcPort, Constants.AUTHENTICATION_FAILURE);
													//                             build_response_pkt(connectPoint,srcMac,dstMac,ipv4Protocol,ipv4SourceAddress,udp_dstport,udp_srcport,Constants.AUTHENTICATION_FAILURE);
													//                             //System.exit(1);
													//                         }
					//if(Constants.DEBUG)
					//	d2 = new Date();
					break;


				case Constants.AUTHENTICATION_STEP_THREE:
					if(Constants.DEBUG){
						log.info("Inside case AUTHENTICATION_STEP_THREE");
					/*	step = 2;
						d1 = d2 = null;
						d1 = new Date();*/
					}
							byte [] b33 =Arrays.copyOfRange(p, 7, 11); //imsi
							byte [] b34 = Arrays.copyOfRange(p, 11, 17); //sep2
							byte [] b35 = Arrays.copyOfRange(p, 17, 25); //res
							
							int imsi3 = ByteBuffer.wrap(b33).getInt();
							imsi = Integer.toString(imsi3);
							
							String sep32 = new String(b34, StandardCharsets.UTF_8); //6 byte
							
							int[] res1 = new int[8];
							// System.out.print("RES : ");
							for(int i=0; i<8; i++){
								res1[i] = b35[i] & 0xFF;
								// System.out.print(" res[" + i + "]= " + res[i]);
							}
							
							StringBuilder resS = new StringBuilder();
							for(int k=0; k<8; k++){
								if(k!=7)
									resS.append(res1[k]);//.append(Constants.INTSEPARATOR);
								else 
									resS.append(res1[k]);
							}
							res = resS.toString();
							if(Constants.BITWISE_DEBUG){
								log.info("Inside case AUTHENTICATION_STEP_THREE");
								log.warn("imsi = {}" , imsi3);
								log.warn("sep2 = {}" , sep32);
								log.warn("RES string: {}" , resS);
							}

					// imsi = tmpArray[1];
					// res = tmpArray[2];	// RES from UE
					if(Constants.DEBUG){
						log.warn("imsi = {}",imsi);
						log.warn(" res = {}",res);
					}
					if(imsi_xres_mapping.containsKey(imsi)){
						String k;
						// for now assuming no auth later figure it out ???????????????????
						if(imsi_xres_mapping.get(imsi).equals(res)){ // UE Authentication (RES == XRES)    
						// if(1==1){ // UE Authentication (RES == XRES)
							imsi_xres_mapping.remove(imsi);
							/*****************UE is authenticated ****************/
							KSI_ASME = "1";
							int replayed_nw_capability = Utils.randInt(0, 10);		// Replayed UE Network Capability decided by MME
							int NAS_integrity_algo_id = Constants.CIPHER_ALGO_MAP.get("HmacSHA1");
							int NAS_cipher_algo_id = Constants.CIPHER_ALGO_MAP.get("AES");
							if(uekey_nas_keys_map.containsKey(imsi)){
								K_ASME = uekey_nas_keys_map.get(imsi)[0];
							}
							else{
								log.info("AUTHENTICATION_STEP_THREE: imsi not found");
								//System.exit(1);
							}
							// K_ASME = uekey_nas_keys_map.get(imsi)[0];
							k = uekey_nas_keys_map.get(imsi)[0];

							// String NAS_keys[] = KDF_NAS(Integer.parseInt(K_ASME), NAS_integrity_algo_id, NAS_cipher_algo_id);		// NAS_keys[0]: Integrity key K_NAS_int, NAS_keys[1]: Encryption key K_NAS_enc
							String NAS_keys[] = KDF_NAS(k, NAS_integrity_algo_id, NAS_cipher_algo_id);		// NAS_keys[0]: Integrity key K_NAS_int, NAS_keys[1]: Encryption key K_NAS_enc

							if(Constants.DEBUG){
								log.warn("AUTHENTICATION_STEP_THREE: INT_KEY= {}", NAS_keys[0]);
								log.warn(" ENC_KEY = {}", NAS_keys[1]);
							}
							// uekey_nas_keys_map.put(imsi, new String[]{K_ASME, NAS_keys[0], NAS_keys[1]});
							uekey_nas_keys_map.put(imsi, new String[]{k, NAS_keys[0], NAS_keys[1]});

							response = new StringBuilder();
							response.append(Constants.NAS_STEP_ONE).append(Constants.SEPARATOR).append(KSI_ASME).append(Constants.SEPARATOR).append(replayed_nw_capability).append(Constants.SEPARATOR).append(NAS_cipher_algo_id).append(Constants.SEPARATOR).append(NAS_integrity_algo_id);

							NAS_MAC = Utils.hmacDigest(response.toString(), NAS_keys[0] + "");	// Generate Message Authentication Code using the hash function
							if(Constants.DEBUG){
								log.warn("AUTHENTICATION_STEP_THREE: Generated NAS MAC= {}", NAS_MAC);
							}
							response.append(Constants.SEPARATOR).append(NAS_MAC);
//                                sendPacket(sw, inPort, destMac, sourceMac, dstIp, srcIp,  IpProtocol.UDP, dstPort, srcPort, response.toString());
							//build_response_pkt(connectPoint,srcMac,dstMac,ipv4Protocol,ipv4SourceAddress,udp_dstport,udp_srcport,response.toString());
							try {
								sendPacketToController(Constants.RAN_IP, response.toString(), (imsi3/1000));
							} catch (NumberFormatException e1) {
                                                		e1.printStackTrace();
		                                                } catch (IOException e1) {
                                                        		e1.printStackTrace();
                                               			 }


							response = null;
						}else{
							log.info(imsi_xres_mapping.get(imsi).equals(res) +" ### "+ imsi_xres_mapping.get(imsi) +" ue_res= "+ res+" ****imsi "+ imsi);
							response = new StringBuilder();
							response.append(Constants.NAS_STEP_ONE).append(Constants.SEPARATOR).append("1").append(Constants.SEPARATOR).append("1").append(Constants.SEPARATOR).append("1").append(Constants.SEPARATOR).append("1");

							NAS_MAC = Utils.hmacDigest(response.toString(), "1234" + "");	// Generate Message Authentication Code using the hash function
							if(Constants.DEBUG){
								log.warn("AUTHENTICATION_STEP_THREE: Generated NAS MAC= {}", NAS_MAC);
							}
							response.append(Constants.SEPARATOR).append(NAS_MAC);
							//response.append(Constants.SEPARATOR).append("938e5f317c9de51b");
							if(Constants.DEBUG){
								log.warn(response.toString());
							}
//                                sendPacket(sw, inPort, destMac, sourceMac, dstIp, srcIp,  IpProtocol.UDP, dstPort, srcPort, Constants.AUTHENTICATION_FAILURE);
							//build_response_pkt(connectPoint,srcMac,dstMac,ipv4Protocol,ipv4SourceAddress,udp_dstport,udp_srcport,Constants.AUTHENTICATION_FAILURE);
							try {
                                                                sendPacketToController(Constants.RAN_IP, response.toString(), (imsi3/1000));
                                                        } catch (NumberFormatException e1) {
                                                                e1.printStackTrace();
                                                                } catch (IOException e1) {
                                                                        e1.printStackTrace();
                                                                 }
							response = null;
							//System.exit(1);
						}
					}else{
						log.info("AUTHENTICATION_STEP_THREE failure");
//                            sendPacket(sw, inPort, destMac, sourceMac, dstIp, srcIp,  IpProtocol.UDP, dstPort, srcPort, Constants.AUTHENTICATION_FAILURE);
						//build_response_pkt(connectPoint,srcMac,dstMac,ipv4Protocol,ipv4SourceAddress,udp_dstport,udp_srcport,Constants.AUTHENTICATION_FAILURE);

						//System.exit(1);
					}
					//if(Constants.DEBUG)
					//	d2 = new Date();
					break;

				case Constants.SEND_APN:

								byte [] b53 =Arrays.copyOfRange(p, 7, 15); //apn
								byte [] b54 = Arrays.copyOfRange(p, 15, 21); //sep2
								byte [] b55 =Arrays.copyOfRange(p, 21, 25); //ue_key

								Long apn = ByteBuffer.wrap(b53).getLong();
								
								String sep52 = new String(b54, StandardCharsets.UTF_8); //6 byte
								
								int ue_key = ByteBuffer.wrap(b55).getInt();
								if(Constants.BITWISE_DEBUG){
									log.info("insisde SEND_APN");
									log.warn("imsi = {}" , apn);
									log.warn("sep2 = {}" , sep52);
									log.warn("ue_key = {}" , ue_key);
								}
								tmpArray[1] = Long.toString(apn);
								tmpArray[2] = Integer.toString(ue_key);
				
//                        DatapathId dgw_dpId = Constants.getDgwDpidFromIp(srcIp.toString()); // returns switchid 1 which corresponds to our connectpoint swid
					//String dgw_dpId = (String)connectPoint.deviceId().toString();  //hardcoding  Device ID format = device:bmv2:s1
					//log.warn("SEND_APN : dgw_dpId = {}",dgw_dpId);
					
					//String array1[]= Constants.SGW_ID1;  // dgw_dpId.split(":");  //parsing the connectpoint to get switch ID
					
					// log.warn("SEND_APN : array1[0] = {}",array1[0]);
					// log.warn("SEND_APN : array1[1] = {}",array1[1]);
					// log.warn("SEND_APN : array1[2]/dgw_dpId = {}",array1[2]);

					String dgw_dpId = "s1"; //array1[2];  // contains switch names like "s10","s1" 

					if(Constants.DEBUG){
						log.info("Inside case SEND_APN");
						/*log.warn("array1[2] = {}",array1[2]); //hardcoding  array1[2] contains switches  like "s1", "s2" etc
						log.warn("dgw_dpId = {}",dgw_dpId); //hardcoding  array1[2] contains switches  like "s1", "s2" etc
						step = 3;
						d1 = d2 = null;
						d1 = new Date();*/
					}
					if(Constants.DO_ENCRYPTION){
						decArray = receiveDecryptedArray(tmpArray);
					}

					//tmpArray[1] => ue apn and tmpArray[2] => ue key
					if(Constants.DEBUG){
						log.warn("received apn={}",tmpArray[1]);
					}
					// storing src port of udp packet to identify the specific UE, when MME wants to initiate connection with this UE.
					// @Offload design map not needed

					// FT.put(Integer.parseInt(Constants.SEND_APN),dgw_dpId, "uekey_udp_src_port_map", tmpArray[2], Integer.toString(udp_srcport));

					String pgw_dpId = hss.getPGateway(tmpArray[1]);  // returns 4 for all apn
					/********************* defaultSwitch is DGW ******************************/
//                        String sgw_dpId = DatapathId.of(Constants.getSgwDpid(defaultSwitch));
					String sgw_dpId = Constants.getSgwDpid(dgw_dpId);
					DeviceId sgwswitchName = Constants.getSgwswitchName(dgw_dpId);
//                        String ip_sgw = sgw.contactPGW(switch_mapping.get(sgw_dpId),switch_mapping.get(pgw_dpId), sgw_dpId, pgw_dpId, tmpArray[1]); //tmpArray[1] => apn of UE
					/*******************install uplink rules on SGW and PGW in this method********************/
					String ip_sgw;
					ip_sgw = sgw.contactPGW(appId,flowRuleService,sgwswitchName,sgw_dpId, pgw_dpId, tmpArray[1]); //tmpArray[1] => apn of UE
					// counter++;
					// if(Constants.MYDEBUG1){
					//     log.warn("counter = {}",counter);
					// }
					response = new StringBuilder();
					response.append(Constants.SEND_IP_SGW_TEID).append(Constants.SEPARATOR).append(ip_sgw).append(Constants.SEPARATOR).append("1").append(Constants.SEPARATOR);

					if(Constants.DO_ENCRYPTION){
						Utils.aesEncrypt(response.toString(), Constants.SAMPLE_ENC_KEY);
						Utils.hmacDigest(response.toString(), Constants.SAMPLE_ENC_KEY);
					}

					tmpArray2 = ip_sgw.split(Constants.SEPARATOR);
					int sgw_teid = Integer.parseInt(tmpArray2[1]);


					if(Constants.DEBUG){
//                            log.info("DEFAULT SWITCH installing uplink rule on default switch dpid = {} inport = {} and SRC IP = {} outPort = {}, and out SRC IP = {}, out teid = {}, of UE key = {}"
//                                    ,defaultSwitch.getLong(),uePort,tmpArray2[0],Constants.ENODEB_SGW_PORT_MAP.get(defaultSwitch.getLong() + Constants.SEPARATOR + Constants.getSgwDpid(defaultSwitch)),Constants.getRanIp(defaultSwitch),sgw_teid,tmpArray[2]);

					}
					/**************************** Uplink flow rules here (DGW to SGW) on DGW switch ***************************/
//                        String SGW_ID =  Integer.parseInt(Constants.getSgwDpid(dgw_dpId));
					int SGW_ID =  Integer.parseInt(Constants.getSgwDpid(dgw_dpId));
					String getval = dgw_dpId.split("s")[1] + Constants.SEPARATOR + SGW_ID;
					int outPort =  Constants.ENODEB_SGW_PORT_MAP.get(getval);
//                        byte[] UE_IPAddr = {10,0,0,3} ;
					byte[] UE_IPAddr = IPv4.toIPv4AddressBytes(tmpArray2[0]);
					if(Constants.DEBUG){
						log.info("#####################################");
						log.warn("dgw_dpid = {}",dgw_dpId);
						log.warn("SGW_ID = {}",SGW_ID);
						log.warn("getval = {}",getval);
						log.info("outPort  ############=  {}",outPort);
						log.info("UE_IPAddr = {}",UE_IPAddr);
					}
					// deviceId is DGW switch name
					// install flow rules by matching on UE_IP
					
					/* UPLINK   => ipv4srcAddr = UE IP and ipv4dstAddr = Sink IP   */
					//fr.insertUplinkTunnelIngressRule(false, appId, flowRuleService, deviceId,UE_IPAddr, Constants.dstSinkIpAddr, sgw_teid, outPort);



//                        installFlowRuleWithIP(dgw_dpId, uePort, Constants.ENODEB_SGW_PORT_MAP.get(dgw_dpId.getLong() + Constants.SEPARATOR + Constants.getSgwDpid(dgw_dpId)), sgw_teid, tmpArray2[0], Constants.getRanIp(dgw_dpId), Constants.getSgwIpUplink(dgw_dpId), Constants.SINK_MAC);
						// key: tmpArray[2] => UE Key, Value: tmpArray2[0] => UE IP
					FT.put(Integer.parseInt(Constants.SEND_APN),dgw_dpId, "uekey_ueip_map", tmpArray[2], tmpArray2[0]); // key: tmpArray[2] => UE Key, Value: tmpArray2[0] => UE IP

					//MAP key = UE KEY,  MAP value = SGW_DPID + SEPARATOR + SGW_TEID
					// @Offload design push sgw_teid to switch table so no need to update in map
					//log.warn("Constants.getSgwDpid(dgw_dpId) = {}",Constants.getSgwDpid(dgw_dpId));
					FT.put(Integer.parseInt(Constants.SEND_APN),dgw_dpId, "uekey_sgw_teid_map", tmpArray[2], Constants.getSgwDpid(dgw_dpId) + Constants.SEPARATOR + tmpArray2[1]);
					

					FT.put(Integer.parseInt(Constants.SEND_APN),dgw_dpId, "sgw_teid_uekey_map", tmpArray2[1], tmpArray[2]);

					// @Offload design push sgw_teid to switch table
					// populates this map on SGW switch
					//DeviceId offload_SGWswitchName1 = Constants.getSgwswitchName(dgw_dpId);
					//fr.populate_uekey_sgwteid_map(false,appId,flowRuleService,offload_SGWswitchName1,Integer.parseInt(tmpArray[2]),sgw_teid);
					//Populate state at local controllers instead of switch
					//sendState(dgw_dpId, action (DEL/PUT), map_Name, key, value) //even delete is considered put
					//sendState(dgw_dpId, "PUT", "uekey_sgw_teid_map", Integer.parseInt(tmpArray[2]), sgw_teid);

//                        sendPacket(sw, inPort, destMac, sourceMac, dstIp, srcIp,  IpProtocol.UDP, dstPort, srcPort, response.toString());
					//build_response_pkt(connectPoint,srcMac,dstMac,ipv4Protocol,ipv4SourceAddress,udp_dstport,udp_srcport,response.toString());
					
					try {
                                                                sendPacketToController(Constants.RAN_IP, response.toString(), ue_key);
                                                        } catch (NumberFormatException e1) {
                                                                e1.printStackTrace();
                                                                } catch (IOException e1) {
                                                                        e1.printStackTrace();
                                                                 }
					response = null;
					if(Constants.DEBUG){
						log.info("Send APN done");
						//d2 = new Date();
					}

					
					break;

				case Constants.SEND_UE_TEID:

								byte [] b73 =Arrays.copyOfRange(p, 7, 11); //ue_teid
								byte [] b74 = Arrays.copyOfRange(p, 11, 17); //sep2
								byte [] b75 =Arrays.copyOfRange(p, 17, 21); //ue_key
								
								int ue_teid = ByteBuffer.wrap(b73).getInt();
								
								String sep72 = new String(b74, StandardCharsets.UTF_8); //6 byte
								
								int ue_key7 = ByteBuffer.wrap(b75).getInt();
								if(Constants.BITWISE_DEBUG){
									log.info("SEND_UE_TEID");
									log.warn("ue_teid = {}" ,ue_teid);
									log.warn("sep2 = {}" , sep72);
									log.warn("imsi = {}" , ue_key7);
								}

								tmpArray[1] = Integer.toString(ue_teid);
								tmpArray[2] = Integer.toString(ue_key7);
				
//                        DatapathId send_ue_teid_dgw = Constants.getDgwDpidFromIp(srcIp.toString());
					//String dgw_dpId1 = (String)connectPoint.deviceId().toString();  //hardcoding  Device ID format = device:bmv2:s1
					//String array5[]= dgw_dpId1.split(":");  //parsing the connectpoint to get switch ID
					String dgw_dpId1 = "s1"; //array5[2];

					String send_ue_teid_dgw = "1"; // Constants.getDgwDpidFromIp(DGW_IPAddr);  // send_ue_teid_dgw contains switches ID like "1", "2" etc
					//log.warn("send_ue_teid_dgw = {}",send_ue_teid_dgw);

					if(Constants.DEBUG){
						log.info("Inside case SEND_UE_TEID");
						log.warn("send_ue_teid_dgw = {}",send_ue_teid_dgw); // send_ue_teid_dgw contains switches ID like "1", "2" etc
						//step = 4;
						//d1 = d2 = null;
						//d1 = new Date();
					}
					if(Constants.DO_ENCRYPTION){
						decArray = receiveDecryptedArray(tmpArray);
					}

					//MAP key = UE KEY,  MAP value = SGW_DPID + SEPARATOR + SGW_TEID
					String tmp = FT.get(send_ue_teid_dgw, "uekey_sgw_teid_map", tmpArray[2]); // tmpArray[2] => ue key
					//log.warn("tmp uekey_sgw_teid_map = {}",tmp);
					tmpArray2 = tmp.split(Constants.SEPARATOR);

					//tmpArray[1] => ue_teId and tmpArray[2] => ue key
					//tmpArray2[0] => sgw_dpId  and tmpArray2[1] => sgw_teID
					if(Constants.DEBUG){
						log.info("inside SEND_UE_TEID");
						log.warn("received ue_teid from RAN = {}",tmpArray[1]);
						log.warn("sgw_dpId = {}",tmpArray2[0]);
						log.warn("sgw_teId = {}",tmpArray2[1]);
					}

//                      modifyBearerRequest(ApplicationId appId,FlowRuleService flowRuleService,DeviceId switchId,String sgw, String sgw_dpId, int sgw_teId, int ue_teId, String key){
					DeviceId SGWswitchName1 = Constants.getSgwswitchName(dgw_dpId1);
					//synchronized (this) {
						sgw.modifyBearerRequest(appId, flowRuleService, SGWswitchName1, tmpArray2[0], tmpArray2[0], Integer.parseInt(tmpArray2[1]), Integer.parseInt(tmpArray[1]), tmpArray[2]);
					//}

					//String ue_ip = uekey_ueip_map.get(tmpArray[2]); // tmpArray[2] => ue key
					String ue_ip = FT.get(send_ue_teid_dgw, "uekey_ueip_map", tmpArray[2]); // tmpArray[2] => ue key


					if(Constants.DEBUG){
						//install downlink rule on default switch
//                            System.out.println("DEFAULT SWITCH installing downlink rule on default switch dpid = "+send_ue_teid_dgw.getLong()+" inport="+Constants.ENODEB_SGW_PORT_MAP.get(send_ue_teid_dgw.getLong() + Constants.SEPARATOR + DatapathId.of(tmpArray2[0]).getLong())+
//                                                       " in teid = " + Integer.parseInt(tmpArray[1]) +
//                                                       " outPort = " + uePort + " out teid= " + Integer.parseInt(tmpArray[1]) + " of UE key = "+tmpArray[2]);
					}
					//System.out.println(DatapathId.of(tmpArray2[0]).getLong());

					/**************************** Downlinkl flow rules on DGW (DGW -> RAN) ***************************/
//                        insertDownlinkTunnelForwardRule(ApplicationId appId,FlowRuleService flowRuleService,DeviceId switchId,int intunId,int outPort,int outtunId,boolean isEgress)
						// fr.insertDownlinkTunnelForwardRule(false,appId, flowRuleService, deviceId,Integer.parseInt(tmpArray[1]), uePort,0,true);
					//fr.insertUplinkTunnelForwardRule(false,appId, flowRuleService, deviceId,Integer.parseInt(tmpArray[1]), uePort,0,true);


//                       installFlowRule(DatapathId dpId, int inPort, int inTunnelId, int outPort, int outTunnelId, String srcIP, String dstIP, String dstMac){
//                      installFlowRule(DatapathId.of(Constants.getDgwDpid(DatapathId.of(tmpArray2[0]))),
//                                                    Constants.ENODEB_SGW_PORT_MAP.get(Constants.getDgwDpid(DatapathId.of(tmpArray2[0])) + Constants.SEPARATOR + DatapathId.of(tmpArray2[0]).getLong()),
//                                                    Integer.parseInt(tmpArray[1]), uePort, Integer.parseInt(tmpArray[1]), Constants.SINK_IP, ue_ip, Constants.getUeMac(send_ue_teid_dgw));

					response = new StringBuilder();
					//NOT USED LATER uekey_guti_map, so not considered in state calc
					//@offload design  : commenting as not needed

						// uekey_guti_map.put(tmpArray[2], (Integer.parseInt(tmpArray[2])+1000)+"");
						// FT.put(Integer.parseInt(Constants.SEND_UE_TEID),send_ue_teid_dgw, "ue_state", tmpArray[2], "1");

						//@offload design 
					// populate all these rules on SGW switch only
					DeviceId offload_SGWswitchName2 = Constants.getSgwswitchName(dgw_dpId1);
					int ue_state = 1;
					//fr.populate_uekey_uestate_map(false,appId,flowRuleService,offload_SGWswitchName2,Integer.parseInt(tmpArray[2]),ue_state);
					//fr.populate_uekey_guti_map(false,appId,flowRuleService,offload_SGWswitchName2,Integer.parseInt(tmpArray[2]),(Integer.parseInt(tmpArray[2])+1000));
					//Populate state at local controllers instead of switch
					//sendState(dgw_dpId, action (DEL/PUT), map_Name, key, value) //even delete is considered put
					//sendState(dgw_dpId1, "PUT", "ue_state", Integer.parseInt(tmpArray[2]), ue_state);
					//sendState(dgw_dpId1, "PUT", "uekey_guti_map", Integer.parseInt(tmpArray[2]), (Integer.parseInt(tmpArray[2])+1000));

					response.append(Constants.ACTUAL_ATTACH_ACCEPT).append(Constants.SEPARATOR).append(Integer.parseInt(tmpArray[2])+1000);	// Sending GUTI

					if(Constants.DO_ENCRYPTION){
						decArray = receiveDecryptedArray(tmpArray);
					}

//                        sendPacket(sw, inPort, destMac, sourceMac, dstIp, srcIp,  IpProtocol.UDP, dstPort, srcPort, response.toString());
					
					//build_response_pkt(connectPoint,srcMac,dstMac,ipv4Protocol,ipv4SourceAddress,udp_dstport,udp_srcport,response.toString());
					
					try {
                                                                sendPacketToController(Constants.RAN_IP, response.toString(), ue_key7);
                                                        } catch (NumberFormatException e1) {
                                                                e1.printStackTrace();
                                                                } catch (IOException e1) {
                                                                        e1.printStackTrace();
                                                                 }
					response = null;
					//if(Constants.DEBUG)
					//	d2 = new Date();
					break;

				case Constants.NAS_STEP_TWO:
					if(Constants.DEBUG)
						log.info("Inside NAS_STEP_TWO");
					break;

				case Constants.DETACH_REQUEST:
//                        DatapathId dw = Constants.getDgwDpidFromIp(srcIp.toString());
									byte [] b93 =Arrays.copyOfRange(p, 7, 11); //ue ip
									byte [] b94 =Arrays.copyOfRange(p, 11, 17); //sep
									byte [] b95 =Arrays.copyOfRange(p, 17, 21); //ue teid
									byte [] b96 =Arrays.copyOfRange(p, 21, 27); //sep
									byte [] b97 =Arrays.copyOfRange(p, 27, 31); //sgw teid
									byte [] b98 =Arrays.copyOfRange(p, 31, 37); //sep
									byte [] b99 =Arrays.copyOfRange(p, 37, 41); //ue num
									
									int ipv4add = IPv4.toIPv4Address(b93);
									String ue_ipaddr = IPv4.fromIPv4Address(ipv4add);
									
									String sep92 = new String(b94, StandardCharsets.UTF_8); //6 byte
									
									int ue_teid9 = ByteBuffer.wrap(b95).getInt();
									
									String sep96 = new String(b96, StandardCharsets.UTF_8); //6 byte
									
									int sgw_teid9 = ByteBuffer.wrap(b97).getInt();
									
									String sep98 = new String(b98, StandardCharsets.UTF_8); //6 byte
									
									int ue_key9 = ByteBuffer.wrap(b99).getInt();
									if(Constants.BITWISE_DEBUG){
										log.info("DETACH_REQUEST");
										log.warn("sep2 = {}" , sep92);
										log.warn("ue_teid = {}" , ue_teid9);
										log.warn("sep3 = {}" , sep96);
										log.warn("sgw_teid = {}" , sgw_teid9);
										log.warn("sep4 = {}" , sep98);
										log.warn("ue_key = {}" , ue_key9);
									}

					//tmpArray[1] => UE IP, tmpArray[2] => UE TEID, tmpArray[3] => SGW TEID, tmpArray[4] => UE_KEY
					tmpArray[1] = ue_ipaddr;
					tmpArray[2] = Integer.toString(ue_teid9);
					tmpArray[3] = Integer.toString(sgw_teid9);
					tmpArray[4] = Integer.toString(ue_key9);

					String dw = "s1"; //(String)connectPoint.deviceId().toString();  //hardcoding
					//String array3[]= dw.split(":");  //hardcoding
					//dw = array3[2];
					if(Constants.DEBUG){
						log.info("Inside case DETACH_REQUEST");
						//log.warn("array3[2] = {}",array3[2]); //hardcoding  array3[2] contains switches  like "s1", "s2" etc
						log.warn(" in DETACH_REQUEST dw = {}",dw); //hardcoding  dw contains switches  like "s1", "s2" etc
						//step = 5;
						//d1 = d2 = null;
						//d1 = new Date();
					}

					if(Constants.DO_ENCRYPTION){
						decArray = receiveDecryptedArray(tmpArray);
					}

					//tmpArray[1] => UE IP, tmpArray[2] => UE TEID, tmpArray[3] => SGW TEID, tmpArray[4] => UE_KEY
					if(Constants.DEBUG){
//                            System.out.println("RECEIVED DETACH REQUEST from UE with ip=" + tmpArray[1] + " TEID=" + tmpArray[2] + " corresponding SGW TEID=" + tmpArray[3] + " UE_KEY=" + tmpArray[4]);
						log.warn("RECEIVED DETACH REQUEST from UE with ip = {} ",tmpArray[1]);
									log.warn("TEID = {}", tmpArray[2]);
											log.warn("corresponding SGW TEID = {}", tmpArray[3]);
													log.warn("UE_KEY = {}", tmpArray[4]);
					}
					//removing the port mapping between UE key and its source port (UDP) used for control traffic
					// tmpArray[4] => UE KEY
					// @Offload design map not needed

					// FT.del(Integer.parseInt(Constants.DETACH_REQUEST),dw, "uekey_udp_src_port_map", tmpArray[4]); // tmpArray[4] => UE KEY

//                        DatapathId pgw_dpid = DatapathId.of(Constants.PGW_ID);
					String pgw_dpid = Integer.toString(Constants.PGW_ID);

					// newly added.. because can't remove in SEND_UE_TEID step.. due to re-establishment of tunnel
						//@offload design  : commenting as not needed

					FT.del(Integer.parseInt(Constants.DETACH_REQUEST),dw, "uekey_sgw_teid_map", tmpArray[4]);// newly added.. because can't remove in SEND_UE_TEID step.. due to re-establishment of tunnel

					// key is sgw teid and value is ue key
					FT.del(Integer.parseInt(Constants.DETACH_REQUEST),dw, "sgw_teid_uekey_map", tmpArray[3]); // key is sgw teid and value is ue key

					//
					FT.del(Integer.parseInt(Constants.DETACH_REQUEST),dw,"uekey_ueip_map", tmpArray[4]);		// key is UE Key and value is UE IP

					//delete uplink rule
					/******************************** delete uplink flow rule on Ingress DGW( DGW -> SGW)********************************/
					// tmpArray[2] contains UE IP as string convert it to byte array
					//tmpArray[1] => UE IP, tmpArray[2] => UE TEID, tmpArray[3] => SGW TEID, tmpArray[4] => UE_KEY
					int SGW_ID2 =  Integer.parseInt(Constants.getSgwDpid(dw));
					String getval2 = dw.split("s")[1] + Constants.SEPARATOR + SGW_ID2;
					outPort =  Constants.ENODEB_SGW_PORT_MAP.get(getval2);
					byte [] UE_IP = IPv4.toIPv4AddressBytes(tmpArray[1]);
					if(Constants.DEBUG){
						log.info("UE IP as received from RAN = {}",tmpArray[1]);
						log.info("Deleting ingress rule with  UE_IPAddr = {}, sgw_teid = {},outPort = {}",UE_IP, Integer.parseInt(tmpArray[3]),outPort);
					}

					/* UPLINK   => ipv4srcAddr = UE IP and ipv4dstAddr = Sink IP   */
					//fr.insertUplinkTunnelIngressRule(true, appId, flowRuleService, deviceId, UE_IP,Constants.dstSinkIpAddr, Integer.parseInt(tmpArray[3]), outPort);

//                        deleteFlowRuleWithIP(dw, uePort, tmpArray[1]); // tmpArray[1] => UE IP
					if(Constants.DEBUG){
						log.warn("DEFAULT SWITCH deleting uplink rule with for UE with IP = {}",tmpArray[1]);
					}
//                        int DEFAULT_S_SGW_PORT = Constants.ENODEB_SGW_PORT_MAP.get(dw.getLong() + Constants.SEPARATOR + Constants.getSgwDpid(dw)); //dpids[0] ==> SGW DPID
					int DEFAULT_S_SGW_PORT = Constants.ENODEB_SGW_PORT_MAP.get(dw.split("s")[1] + Constants.SEPARATOR + Constants.getSgwDpid(dw)); //dpids[0] ==> SGW DPID
					//delete downlink rule
					/***********************************delete downlink flow rule on Egress DGW( DGW -> RAN)*************************/
//                        insertDownlinkTunnelForwardRule(boolean removeRule,ApplicationId appId,FlowRuleService flowRuleService,DeviceId switchId,int intunId,int outPort,int outtunId,boolean isEgress) {
					//synchronized (this) {
						// fr.insertDownlinkTunnelForwardRule(true, appId, flowRuleService, deviceId, Integer.parseInt(tmpArray[2]), uePort, 0, true);
					//fr.insertUplinkTunnelForwardRule(true, appId, flowRuleService, deviceId, Integer.parseInt(tmpArray[2]), uePort, 0, true);

					//}

//                        deleteFlowRuleWithTEID(dw, DEFAULT_S_SGW_PORT, Integer.parseInt(tmpArray[2]), Constants.SINK_IP); //tmpArray[2] ==> UE VLAN ID
					if(Constants.DEBUG){
//                            System.out.println("DEFAULT SWITCH deleting downlink rule with for UE with IP="+tmpArray[1]+" and UE TEID="+tmpArray[2]);
						log.warn("DEFAULT SWITCH deleting downlink rule with for UE with IP = {}",tmpArray[1]);
						log.warn(" and UE TEID = {}",tmpArray[2]);
					}

					// dpids[0] ==> SGW DPID   & dpids[1]==> PGW DPID
//                        boolean status = sgw.detachUEFromSGW(switch_mapping.get(DatapathId.of(Constants.getSgwDpid(dw))), switch_mapping.get(pgw_dpid), DatapathId.of(Constants.getSgwDpid(dw)), pgw_dpid, Integer.parseInt(tmpArray[3]), tmpArray[1]);
					DeviceId SGWswitchName2 = Constants.getSgwswitchName(dw);
//                        public boolean detachUEFromSGW(String sgw_dpId, String pgw_dpId, int sgw_teid, String ue_ip) {
					boolean status = sgw.detachUEFromSGW(appId,flowRuleService,SGWswitchName2,Constants.getSgwDpid(dw), pgw_dpid, Integer.parseInt(tmpArray[3]), tmpArray[1]);
					response = new StringBuilder();
					
					if(status){
						response.append(Constants.DETACH_ACCEPT).append(Constants.SEPARATOR).append("");
						if(Constants.DO_ENCRYPTION){
							Utils.aesEncrypt(response.toString(), Constants.SAMPLE_ENC_KEY);
							Utils.hmacDigest(response.toString(), Constants.SAMPLE_ENC_KEY);
						}
//                            sendPacket(sw, inPort, destMac, sourceMac, dstIp, srcIp,  IpProtocol.UDP, dstPort, srcPort, response.toString());
						if(Constants.DEBUG){
							log.info(" sending response in DETACH_REQUEST");
						}
						DeviceId offload_SGWswitchName3 = Constants.getSgwswitchName(dw);

						// @offload design : remove populated auxilary tables from SGW switch in detach case
						// while deleting rules we dont need match values so sendong match parameters as 0 in all cases
						//fr.populate_uekey_uestate_map(true,appId,flowRuleService,offload_SGWswitchName3,Integer.parseInt(tmpArray[4]),0);
						//fr.populate_uekey_guti_map(true,appId,flowRuleService,offload_SGWswitchName3,Integer.parseInt(tmpArray[4]),0);
						//fr.populate_uekey_sgwteid_map(true,appId,flowRuleService,offload_SGWswitchName3,Integer.parseInt(tmpArray[4]),0);
						
						//Populate state at local controllers instead of switch
						//sendState(dgw_dpId, action (DEL/PUT), map_Name, key, value) //even delete is considered put
						//sendState(dw, "DEL", "ue_state", Integer.parseInt(tmpArray[4]), 0);
						//sendState(dw, "DEL", "uekey_guti_map", Integer.parseInt(tmpArray[4]), 0);
						//sendState(dw, "DEL", "uekey_sgw_teid_map", Integer.parseInt(tmpArray[4]), 0);

						//build_response_pkt(connectPoint,srcMac,dstMac,ipv4Protocol,ipv4SourceAddress,udp_dstport,udp_srcport,response.toString());
						try {
                                                                sendPacketToController(Constants.RAN_IP, response.toString(), ue_key9);
                                                        } catch (NumberFormatException e1) {
                                                                e1.printStackTrace();
                                                                } catch (IOException e1) {
                                                                        e1.printStackTrace();
                                                                 }
					}else{
						response.append(Constants.DETACH_FAILURE).append(Constants.SEPARATOR).append("");
						if(Constants.DO_ENCRYPTION){
							Utils.aesEncrypt(response.toString(), Constants.SAMPLE_ENC_KEY);
							Utils.hmacDigest(response.toString(), Constants.SAMPLE_ENC_KEY);
						}
//                            sendPacket(sw, inPort, destMac, sourceMac, dstIp, srcIp,  IpProtocol.UDP, dstPort, srcPort, response.toString());
						//build_response_pkt(connectPoint,srcMac,dstMac,ipv4Protocol,ipv4SourceAddress,udp_dstport,udp_srcport,response.toString());
						try {
                                                                sendPacketToController(Constants.RAN_IP, response.toString(), ue_key9);
                                                        } catch (NumberFormatException e1) {
                                                                e1.printStackTrace();
                                                                } catch (IOException e1) {
                                                                        e1.printStackTrace();
                                                                 }

//                            System.out.println("ERROR: DETACH_FAILURE");
						log.info("ERROR: DETACH_FAILURE");
						//System.exit(1);
					}
					response = null;
					//if(Constants.DEBUG)
					//	d2 = new Date();
					break;

				/************************************************* CONTEXT RELEASE ****************************************************/

				case Constants.UE_CONTEXT_RELEASE_REQUEST:
					// @offload design it will be handled by local onos controller

//                                 byte [] b143 =Arrays.copyOfRange(p, 7, 11); //ue ip
//                                 byte [] b144 =Arrays.copyOfRange(p, 11, 17); //sep
//                                 byte [] b145 =Arrays.copyOfRange(p, 17, 21); //ue teid
//                                 byte [] b146 =Arrays.copyOfRange(p, 21, 27); //sep
//                                 byte [] b147 =Arrays.copyOfRange(p, 27, 31); //sgw teid
//                                 byte [] b148 =Arrays.copyOfRange(p, 31, 37); //sep
//                                 byte [] b149 =Arrays.copyOfRange(p, 37, 41); //ue num
							
//                                 int ipv4add1 = IPv4.toIPv4Address(b143);
//                                 String ue_ipaddr1 = IPv4.fromIPv4Address(ipv4add1);
//                                 tmpArray[1]=ue_ipaddr1;

//                                 String sep142 = new String(b144, StandardCharsets.UTF_8); //6 byte
							
//                                 int ue_teid14 = ByteBuffer.wrap(b145).getInt();
//                                 tmpArray[2] = Integer.toString(ue_teid14);
							
//                                 String sep146 = new String(b146, StandardCharsets.UTF_8); //6 byte
							
//                                 int sgw_teid14 = ByteBuffer.wrap(b147).getInt();
//                                 tmpArray[3] = Integer.toString(sgw_teid14);
							
//                                 String sep148 = new String(b148, StandardCharsets.UTF_8); //6 byte
							
//                                 int ue_num14 = ByteBuffer.wrap(b149).getInt();
//                                 tmpArray[4] = Integer.toString(ue_num14);

//                                 if(Constants.BITWISE_DEBUG){
//                                     log.info("UE_CONTEXT_RELEASE_REQUEST");
//                                     log.warn("ue_ipaddr ={}",ue_ipaddr1);
//                                     log.warn("sep2 = {}" , sep142);
//                                     log.warn("ue_teid = {}" , ue_teid14);
//                                     log.warn("sep3 = {}" , sep146);
//                                     log.warn("sgw_teid = {}" , sgw_teid14);
//                                     log.warn("sep4 = {}" , sep148);
//                                     log.warn("ue_num = {}" , ue_num14);
//                                 }

// //                        DatapathId dw_cr = Constants.getDgwDpidFromIp(srcIp.toString());
//                         String dw_cr = Constants.getDgwDpidFromIp(DGW_IPAddr);  // dw_cr contains switches ID like "1", "2" etc
//                         if(Constants.DEBUG){
//                             log.info("Inside case UE_CONTEXT_RELEASE_REQUEST");
//                             //tmpArray[1]==> UE IP  &  tmpArray[2] ==> UE TEID  &  tmpArray[3] ==> SGW TEID &  tmpArray[4] ==> UE_KEY
//                             log.info("RECEIVED UE CONTEXT RELEASE REQUEST from UE with ip = {}, TEID= {}, corresponding SGW TEID = {}, UE KEY = {}" , tmpArray[1] ,tmpArray[2], tmpArray[3] , tmpArray[4]);
//                             step = 7;
//                             d1 = d2 = null;
//                             d1 = new Date();
//                         }

//                         //delete uplink rule
//                         /******************************** delete uplink flow rule on Ingress DGW( DGW -> SGW)********************************/
//                         byte [] UE_IP1 = IPv4.toIPv4AddressBytes(tmpArray[1]);
//                         if(Constants.DEBUG){
//                             log.info("UE IP as received from RAN = {}",tmpArray[1]);
//                             log.info("Deleting ingress rule with deiveId = {}, UE_IPAddr = {}, sgw_teid = {},outPort = {}",deviceId,UE_IP1, Integer.parseInt(tmpArray[3]),outPort);
//                         }

//                         /* UPLINK   => ipv4srcAddr = UE IP and ipv4dstAddr = Sink IP   */
//                         fr.insertUplinkTunnelIngressRule(true,appId,flowRuleService,deviceId,UE_IP1,Constants.dstSinkIpAddr,Integer.parseInt(tmpArray[3]),outPort);


// //                        deleteFlowRuleWithIP(dw_cr, uePort, tmpArray[1]); //tmpArray[1] ==> UE IP
//                         if(Constants.DEBUG){
//                             log.info("DEFAULT SWITCH deleting uplink rule with for UE with IP = {}",tmpArray[1]);
//                         }

//                         DEFAULT_S_SGW_PORT = Constants.ENODEB_SGW_PORT_MAP.get(dw_cr + Constants.SEPARATOR + Constants.getSgwDpid(dw_cr)); //dpids[0] ==> SGW DPID
//                         //delete downlink rule
//                         /***********************************delete downlink flow rule on Egress DGW( DGW -> RAN)*************************/
//                         fr.insertUplinkTunnelForwardRule(true,appId, flowRuleService, deviceId,Integer.parseInt(tmpArray[2]), uePort,0,true);


// //                        deleteFlowRuleWithTEID(dw_cr, DEFAULT_S_SGW_PORT, Integer.parseInt(tmpArray[2]), Constants.SINK_IP); //tmpArray[2] ==> UE VLAN ID
//                         if(Constants.DEBUG){
//                             log.info("DEFAULT SWITCH deleting downlink rule with for UE with IP = {} and UE TEID = {}",tmpArray[1],tmpArray[2]);
//                         }

//                         // dpids[0] ==> SGW DPID   & dpids[1]==> PGW DPID
// //                        public void releaseAccessBearersRequest(ApplicationId appId,FlowRuleService flowRuleService,DeviceId SGWswitchId, String sgw_dpId, int sgw_teid, String ue_ip){
//                         DeviceId SGWswitchName3 = Constants.getSgwswitchName(dw_cr);
//                         sgw.releaseAccessBearersRequest(appId,flowRuleService,SGWswitchName3, Constants.getSgwDpid(dw_cr), Integer.parseInt(tmpArray[3]), tmpArray[1]);

//                         response = new StringBuilder();
//                         FT.put(Integer.parseInt(Constants.UE_CONTEXT_RELEASE_REQUEST),dw_cr, "ue_state", tmpArray[4], "0");

//                         response.append(Constants.UE_CONTEXT_RELEASE_COMMAND).append(Constants.SEPARATOR).append("");
// //                        private void build_response_pkt(ConnectPoint connectPoint,MacAddress srcMac,MacAddress dstMac,byte ipv4Protocol,int ipv4SourceAddress,int udp_dstport,int udp_srcport,String response){
//                         build_response_pkt(connectPoint,srcMac,dstMac,ipv4Protocol,ipv4SourceAddress,udp_dstport,udp_srcport,response.toString());

// //                        sendPacket(sw, inPort, destMac, sourceMac, dstIp, srcIp,  IpProtocol.UDP, dstPort, srcPort, response.toString());
//                         response = null;
//                         if(Constants.DEBUG)
//                             d2 = new Date();
					break;

				/**********************************  UE_INITIATED SERVICE REQUEST ***************************************/

				case Constants.UE_SERVICE_REQUEST:
					// @offload design it will be handled by local onos controller


//                                         byte [] b173 =Arrays.copyOfRange(p, 7, 11); //ue num
//                                         byte [] b174 =Arrays.copyOfRange(p, 11, 17); //sep
//                                         byte [] b175 =Arrays.copyOfRange(p, 17, 21); //ksi asme
//                                         byte [] b176 =Arrays.copyOfRange(p, 21, 27); //sep
//                                         byte [] b177 =Arrays.copyOfRange(p, 27, 31); //ue ip
									
//                                         int ue_num17 = ByteBuffer.wrap(b173).getInt();
//                                         tmpArray[1] = Integer.toString(ue_num17);
									
//                                         String sep172 = new String(b174, StandardCharsets.UTF_8); //6 byte
									
//                                         int ksi_asme17 = ByteBuffer.wrap(b175).getInt();
//                                         tmpArray[2] = Integer.toString(ksi_asme17);
									
//                                         String sep176 = new String(b176, StandardCharsets.UTF_8); //6 byte
									

//                                         int ipv4add2 = IPv4.toIPv4Address(b177);
//                                         String ue_ipaddr2 = IPv4.fromIPv4Address(ipv4add2);
//                                         tmpArray[3]=ue_ipaddr2;

//                                         if(Constants.BITWISE_DEBUG){
//                                             log.info("UE_SERVICE_REQUEST");
//                                             log.warn("UE_KEY ={}",tmpArray[1]);
//                                             log.warn("sep1 = {}" , sep172);
//                                             log.warn("KSI_ASME = {}",tmpArray[2]);
//                                             log.warn("sep2 = {}" , sep176);
//                                             log.warn("UE_IP = {}" , ue_ipaddr2);
//                                         }

// //                        DatapathId dw_ue_ser = Constants.getDgwDpidFromIp(srcIp.toString());
//                         String dw_ue_ser = Constants.getDgwDpidFromIp(DGW_IPAddr);  // dw_ue_ser contains switches ID like "1", "2" etc

//                         if(Constants.DEBUG){
//                             log.info("Inside case UE_SERVICE_REQUEST");
//                             step = 9;
//                             d1 = d2 = null;
//                             d1 = new Date();
//                         }
//                         //tmpArray[1]==> UE_KEY  &  tmpArray[2] ==> KSI_ASME & tmpArray[3] ==> UE_IP
//                         if(Constants.DEBUG){
//                             log.info("RECEIVED UE_SERVICE_REQUEST from UE with key = {} KSI_ASME = {}", tmpArray[1], tmpArray[2]);
//                         }
//                         if(Constants.DO_ENCRYPTION){
//                             decArray = receiveDecryptedArray(tmpArray);
//                         }
// //                        sgw_dpId = DatapathId.of(Constants.getSgwDpid(defaultSwitch));
//                         sgw_dpId = Constants.getSgwDpid(dw_ue_ser);
//                         ue_ip = tmpArray[3];

//                         String sgw_dpid_sgw_teid = FT.get(dw_ue_ser,"uekey_sgw_teid_map",tmpArray[1]); // MAP key = UE KEY,  MAP value = SGW_DPID + SEPARATOR + SGW_TEID
//                         tmpArray2 = sgw_dpid_sgw_teid.split(Constants.SEPARATOR);
//                         sgw_teid = Integer.parseInt(tmpArray2[1]);

//                         //install uplink rule on default switch
//                         if(Constants.DEBUG){
// //                            System.out.println("DEFAULT SWITCH installing uplink rule on default switch dpid = "+dw_ue_ser.getLong()+" inport="+uePort+" and SRC IP = "+ue_ip+
// //                                                       " outPort = "+Constants.ENODEB_SGW_PORT_MAP.get(dw_ue_ser + Constants.SEPARATOR + sgw_dpId.getLong())+" and out SRC IP = "+Constants.getRanIp(dw_ue_ser)+" out teid= "+sgw_teid+" of UE key = "+tmpArray[1]);
//                         }

//                         /**************************** Uplink flow rules here (DGW to SGW) on DGW switch ***************************/
// //                        String SGW_ID =  Integer.parseInt(Constants.getSgwDpid(dgw_dpId));
//                         int SGW_ID1 =  Integer.parseInt(Constants.getSgwDpid(dw_ue_ser));
//                         String getval1 = dw_ue_ser + Constants.SEPARATOR + SGW_ID1;
//                         int outPort1 =  Constants.ENODEB_SGW_PORT_MAP.get(getval1);

//                         byte[] UE_IPAddr1 = IPv4.toIPv4AddressBytes(tmpArray[3]);

//                         // deviceId is DGW switch name
//                         // install flow rules by matching on UE_IP

//                         /* UPLINK   => ipv4srcAddr = UE IP and ipv4dstAddr = Sink IP   */
//                         fr.insertUplinkTunnelIngressRule(false,appId,flowRuleService,deviceId,UE_IPAddr1,Constants.dstSinkIpAddr, sgw_teid,outPort1);

//                         //        private void installFlowRuleWithIP(DatapathId dpId, int inPort, int outPort, int outTunnelId, String UE_IP, String srcIP, String dstIP, String dstMac){
// //                        installFlowRuleWithIP(dw_ue_ser, uePort, Constants.ENODEB_SGW_PORT_MAP.get(dw_ue_ser.getLong() + Constants.SEPARATOR + Constants.getSgwDpid(dw_ue_ser)), sgw_teid, ue_ip, Constants.getRanIp(dw_ue_ser), Constants.getSgwIpUplink(dw_ue_ser), Constants.SINK_MAC);

//                         response = new StringBuilder();
//                         response.append(Constants.INITIAL_CONTEXT_SETUP_REQUEST).append(Constants.SEPARATOR).append(sgw_teid);

//                         if(Constants.DO_ENCRYPTION){
//                             decArray = receiveDecryptedArray(tmpArray);
//                         }

// //                        sendPacket(sw, inPort, destMac, sourceMac, dstIp, srcIp,  IpProtocol.UDP, dstPort, srcPort, response.toString());
//                         build_response_pkt(connectPoint,srcMac,dstMac,ipv4Protocol,ipv4SourceAddress,udp_dstport,udp_srcport,response.toString());
//                         response = null;
//                         if(Constants.DEBUG)
//                             d2 = new Date();
					break;

				case Constants.INITIAL_CONTEXT_SETUP_RESPONSE:
					// @offload design it will be handled by local onos controller

//                                     byte [] b193 =Arrays.copyOfRange(p, 7, 11); //ue teid
//                                     byte [] b194 =Arrays.copyOfRange(p, 11, 17); //sep
//                                     byte [] b195 =Arrays.copyOfRange(p, 17, 21); //ue key
//                                     byte [] b196 =Arrays.copyOfRange(p, 21, 27); //sep
//                                     byte [] b197 =Arrays.copyOfRange(p, 27, 31); //ue ip

								
//                                     int ue_teid19 = ByteBuffer.wrap(b193).getInt();
//                                     System.out.println("ue_teid = " + ue_teid19);
//                                     tmpArray[1]=Integer.toString(ue_teid19);
								
//                                     String sep192 = new String(b194, StandardCharsets.UTF_8); //6 byte
//                                     System.out.println("sep2 = " + sep192);
								
//                                     int ue_key19 = ByteBuffer.wrap(b195).getInt();
//                                     System.out.println("ue_key = " + ue_key19);
//                                     tmpArray[2]=Integer.toString(ue_key19);
								
//                                     String sep193 = new String(b196, StandardCharsets.UTF_8); //6 byte
//                                     System.out.println("sep3 = " + sep193);
								
//                                     // int[] ip19 = new int[4];
//                                     // System.out.print("IP = ");
//                                     // for(int i=0; i<4; i++){
//                                     //     ip19[i] = b197[i]& 0xFF;
//                                     //     System.out.print(ip19[i]);
//                                     // }
//                                     // System.out.println();

//                                     int ipv4add3 = IPv4.toIPv4Address(b197);
//                                     String ue_ipaddr3 = IPv4.fromIPv4Address(ipv4add3);
//                                     tmpArray[3]=ue_ipaddr3;

//                                     if(Constants.BITWISE_DEBUG){
//                                         log.info("INITIAL_CONTEXT_SETUP_RESPONSE");
//                                         log.warn("ue_teId ={}",tmpArray[1]);
//                                         log.warn("sep1 = {}" , sep192);
//                                         log.warn("key = {}" ,tmpArray[2]);
//                                         log.warn("sep2 = {}" , sep193);
//                                         log.warn("UE_IP = {}" , tmpArray[3]);
//                                     }

//                         String dw_c_resp = Constants.getDgwDpidFromIp(DGW_IPAddr);
//                         if(Constants.DEBUG){
//                             log.info("Inside case INITIAL_CONTEXT_SETUP_RESPONSE");
//                             step = 10;
//                             d1 = d2 = null;
//                             d1 = new Date();
//                         }
//                         if(Constants.DO_ENCRYPTION){
//                             decArray = receiveDecryptedArray(tmpArray);
//                         }

//                         //tmpArray[1] => ue_teId, tmpArray[2] => ue key & tmpArray[3] => ue ip
//                         if(Constants.DEBUG){
//                             log.info("received teid = {}",tmpArray[1]);
//                         }

//                         tmp = FT.get(dw_c_resp, "uekey_sgw_teid_map", tmpArray[2]); // tmpArray[2] => ue key
//                         tmpArray2 = tmp.split(Constants.SEPARATOR);
//                         //tmpArray2[0] => sgw_dpId  and tmpArray2[1] => sgw_teID


// //                      modifyBearerRequest(ApplicationId appId,FlowRuleService flowRuleService,DeviceId switchId,String sgw, String sgw_dpId, int sgw_teId, int ue_teId, String key){
//                         DeviceId SGWswitchName4 = Constants.getSgwswitchName(dw_c_resp);
//                         sgw.modifyBearerRequest(appId,flowRuleService,SGWswitchName4,tmpArray2[0], tmpArray2[0], Integer.parseInt(tmpArray2[1]), Integer.parseInt(tmpArray[1]), tmpArray[2]);


// //                        sgw.modifyBearerRequest(switch_mapping.get(DatapathId.of(tmpArray2[0])), DatapathId.of(tmpArray2[0]), Integer.parseInt(tmpArray2[1]), Integer.parseInt(tmpArray[1]), tmpArray[2]);

//                         ue_ip = tmpArray[3];

//                         if(Constants.DEBUG){
// //                            System.out.println("DEFAULT SWITCH installing downlink rule on default switch dpid = "+dw_c_resp.getLong()+" inport="+Constants.ENODEB_SGW_PORT_MAP.get(dw_c_resp.getLong() + Constants.SEPARATOR + DatapathId.of(tmpArray2[0]).getLong())+
// //                                                       " in teid = " + Integer.parseInt(tmpArray[1]) +
// //                                                       " outPort = " + uePort + " out teid= " + Integer.parseInt(tmpArray[1]) + " of UE key = "+tmpArray[2]);
//                         }
// //                        insertDownlinkTunnelForwardRule(ApplicationId appId,FlowRuleService flowRuleService,DeviceId switchId,int intunId,int outPort,int outtunId,boolean isEgress)
//                         // fr.insertDownlinkTunnelForwardRule(false,appId, flowRuleService, deviceId,Integer.parseInt(tmpArray[1]), uePort,0,true);

					/**************************** Downlink flow rules on DGW (DGW -> RAN) ***************************/
//                         fr.insertUplinkTunnelForwardRule(false,appId, flowRuleService, deviceId,Integer.parseInt(tmpArray[1]), uePort,0,true);



// //                        installFlowRule( DatapathId.of(Constants.getDgwDpid(DatapathId.of(tmpArray2[0]))), Constants.ENODEB_SGW_PORT_MAP.get(Constants.getDgwDpid(DatapathId.of(tmpArray2[0])) + Constants.SEPARATOR + DatapathId.of(tmpArray2[0]).getLong()), Integer.parseInt(tmpArray[1]), uePort, Integer.parseInt(tmpArray[1]), Constants.SINK_IP, ue_ip, Constants.getUeMac(dw_c_resp));

//                         response = new StringBuilder();
//                         //NOT USED uekey_guti_map, not considered
//                         uekey_guti_map.put(tmpArray[2], (Integer.parseInt(tmpArray[2])+1000)+"");
//                         FT.put(Integer.parseInt(Constants.INITIAL_CONTEXT_SETUP_RESPONSE),dw_c_resp, "ue_state", tmpArray[2], "1");
//                         response.append(Constants.ATTACH_ACCEPT).append(Constants.SEPARATOR).append(tmpArray[2]);

//                         if(Constants.DO_ENCRYPTION){
//                             decArray = receiveDecryptedArray(tmpArray);
//                         }

// //                        sendPacket(sw, inPort, destMac, sourceMac, dstIp, srcIp,  IpProtocol.UDP, dstPort, srcPort, response.toString());
//                         build_response_pkt(connectPoint,srcMac,dstMac,ipv4Protocol,ipv4SourceAddress,udp_dstport,udp_srcport,response.toString());

//                         response = null;
//                         if(Constants.DEBUG)
//                             d2 = new Date();
					break;





				default:
					if(Constants.DEBUG){
						log.info("Inside case default");
						//step = 11;
						//d1 = d2 = null;
						//d1 = new Date();
					}

					if(tmpArray.length == 3){
									byte [] b203 =Arrays.copyOfRange(p, 7, 27); //enc hash
									byte [] b204 = Arrays.copyOfRange(p, 27, 33); //sep2
									byte [] b205 =Arrays.copyOfRange(p, 33, 37); //imsi
									
									String enc_hash = new String(b203, StandardCharsets.UTF_8); //6 byte
									
									String sep202 = new String(b204, StandardCharsets.UTF_8); //6 byte
									
									int imsi205 = ByteBuffer.wrap(b205).getInt();

									if(Constants.BITWISE_DEBUG){
										log.info("NAS STEP TWO");
										log.warn("enc_hash = {}" , enc_hash);
										log.warn("sep2 = {}" , sep202);
										log.warn("imsi = {}" , imsi205);
									}
				
						if(Constants.DEBUG){
							//log.warn("NAS STEP TWO: arr length = {}", arr.length);
							log.warn(" Received encrypted text = {}", enc_hash);
							// log.warn(" NAS-MAC = {}", tmpArray[1] );
							log.warn( " IMSI = {}", imsi205);
							log.warn("Encrypted length={}",  enc_hash.length());
							// log.warn(" NAS-MAC length{}=" , tmpArray[1].length());
							log.warn( " IMSI length={}",Integer.toString(imsi205).length());
						}
						if(!Constants.CHECK_INTEGRITY){
							//d2 = new Date();
							break;
						}

						// NAS_Keys = uekey_nas_keys_map.get(tmpArray[2]);
						NAS_Keys = uekey_nas_keys_map.get(Integer.toString(imsi205));

						// NAS_MAC = Utils.hmacDigest(tmpArray[0], NAS_Keys[1]);
						NAS_MAC = Utils.hmacDigest(enc_hash, NAS_Keys[1]);
						if(Constants.DEBUG){
							log.warn("NAS_STEP_TWO: Generated NAS MAC= {}" , NAS_MAC);
						}
					}
					else{
						log.warn("ERROR: NAS STEP TWO: unknown command. Array length = {}" , tmpArray.length);
						log.warn(" Received: {}" , payload);
						//System.exit(1);
					}
					//d2 = new Date();
			}
			//if(Constants.DEBUG)
			//	timeDiff(d1, d2, step);
		}

	}
		

}

	/* 	public void processControllerPacket(String msg){
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
	}*/

//}
