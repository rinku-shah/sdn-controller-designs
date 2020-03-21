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
import io.lettuce.core.*;
import io.lettuce.core.event.*;
import io.lettuce.core.api.StatefulRedisConnection;
//import io.reactor.*; //core.scheduler.*;
import org.slf4j.Logger;
import static org.slf4j.LoggerFactory.getLogger;

public class KV {
    private static final Logger log = getLogger(EpcApp.class);

	public KV() {
//		Jedis jedis = new Jedis("192.168.100.1");		
		//log.warn("Jedis connected");
		try{
			nl.melp.redis.Redis r = new nl.melp.redis.Redis(new Socket("127.0.0.1", 6379));
		for(int i=1; i<=100000; i++){
			r.call("SET", "foo"+i, Integer.toString(i));
		}
		//r.call("INCRBY", "foo", "456");
		String out = new String((byte[])(r.call("GET", "foo25")));
		//String out = Base64.getEncoder().encodeToString(r.call("GET", "foo"));
		log.warn("GET value = {}", out); // will print '579'

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
