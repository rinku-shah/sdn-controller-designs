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
//import redis.clients.jedis.Jedis;
/*import io.lettuce.core.*;
import io.lettuce.core.event.*;
import io.lettuce.core.api.StatefulRedisConnection;
//import io.reactor.*; //core.scheduler.*;*/
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
		try{
			String out = new String((byte[])(r.call("GET", key)));
			return out;
		} catch (IOException e) {
            		e.printStackTrace();
			log.warn("GET: Redis exception occured");
            	}
        	return null;
    	}

        public Long del(String key){
		Long out = new Long(0);
                try{
                        out = r.call("DEL", key);
                        //return out;
                } catch (IOException e) {
                        e.printStackTrace();
                        log.warn("DEL: Redis exception occured");
                }
                return out;
        }


	public KV() {
//		Jedis jedis = new Jedis("192.168.100.1");		
		//log.warn("Jedis connected");
		try{
			r = new nl.melp.redis.Redis(new Socket("127.0.0.1", 6379));
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
		//RedisURI redisUri = RedisURI.Builder.redis("localhost")
                                //.withPassword("authentication")
                                //.withDatabase(2)
                                //.build();
		//RedisClient client = RedisClient.create(redisUri);
		//RedisClient client = RedisClient.create("redis://localhost:6379");
		//StatefulRedisConnection<String, String> connection = client.connect();
		//RedisStringCommands sync = connection.sync();
		//String value = sync.get("key");
	}
}

