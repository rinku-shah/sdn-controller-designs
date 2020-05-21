/*****************************************************************
 * This class contains the code of Home Subscriber Server (HSS). *
 * This class connects to the MySql database containing UE      *
 * specific data for verifying the UE details and establish a    *
 * secure communication thereafter                               *
 *****************************************************************/

package org.onosproject.p4tutorial.epc;
import java.util.*;
import java.io.*;
import java.net.*;

import org.slf4j.Logger;
import static org.slf4j.LoggerFactory.getLogger;

public class KV {
    private static final Logger log = getLogger(EpcApp.class);
    public nl.melp.redis.Redis r;
    
    public void put(String key, String value){
		try{
			r.call("SET", key, value);
		} catch (IOException e) {
            e.printStackTrace();
			log.warn("SET: Redis exception occured");
        }
	}

	public String get(String key){
		String out = null;
		try{
			out = new String((byte[])(r.call("GET", key)));
		} catch (IOException e) {
            e.printStackTrace();
			log.warn("GET: Redis exception occured");
        }
        return out;
    }

    public Long del(String key){
		Long out = new Long(0);
	    try{
	        out = r.call("DEL", key);
	    } catch (IOException e) {
	        e.printStackTrace();
	        log.warn("DEL: Redis exception occured");
	    }
	    return out;
    }

	public KV() {
		try{
			r = new nl.melp.redis.Redis(new Socket("192.168.100.101", 6379));
			nl.melp.redis.Redis r = new nl.melp.redis.Redis(new Socket("192.168.100.101", 6379));
			r.call("FLUSHALL");

			for(int i=1; i<=10; i++){
				//r.call("SET", "foo"+i, Integer.toString(i));
				put("foo"+i, Integer.toString(i));
			}
			//r.call("INCRBY", "foo", "456");
			//String out = new String((byte[])(r.call("GET", "foo25")));
			//String out = Base64.getEncoder().encodeToString(r.call("GET", "foo"));
			log.warn("GET value = {}", get("foo10")); // will print '579'
			log.warn("DELETE response = {}", del("foo10"));
			log.warn("DELETE response = {}", del("foo100"));

        } catch (IOException e) {
            e.printStackTrace();
			log.warn("Redis exception occured");
        }
	}
}

