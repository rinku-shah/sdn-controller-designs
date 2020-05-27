/*****************************************************************
 * This class contains the code of Home Subscriber Server (HSS). *
 * This class connects to the MySql database containing UE      *
 * specific data for verifying the UE details and establish a    *
 * secure communication thereafter                               *
 *****************************************************************/

package org.onosproject.p4tutorial.epc;
import java.util.*;
import redis.clients.jedis.Jedis;

import org.slf4j.Logger;
import static org.slf4j.LoggerFactory.getLogger;

public class KV {
    private static final Logger log = getLogger(EpcApp.class);

	public KV() {
		Jedis jedis = new Jedis("192.168.100.1");		
		//log.warn("Jedis connected");
	}
}
