import redis.clients.jedis.Jedis; 
import java.util.*;

public class RedisKeyJava { 
  
    // Generic function to convert set to list 
    public static <T> List<T> convertSetToList(Set<T> set) 
    { 
        // create an empty list 
        List<T> list = new ArrayList<>(); 
  
        // push each element in the set into the list 
        for (T t : set) 
            list.add(t); 
  
        // return the list 
        return list; 
    }  

  public static void main(String[] args) { 
   
      //Connecting to Redis server on localhost 
      Jedis jedis = new Jedis("localhost"); 
      System.out.println("Connection to server sucessfully"); 
      //store data in redis list 
      // Get the stored data and print it 
      //List<String> list = jedis.keys("*"); 
      jedis.flushDB();
      List<String> list = convertSetToList(jedis.keys("*"));
      
      for(int i = 0; i<list.size(); i++) { 
         System.out.println("List of stored keys:: "+list.get(i)); 
      }
	jedis.set("First","1");
	jedis.set("Second", "2");
	System.out.println("Get: \"First\"= "+jedis.get("First"));
	jedis.del("First");

	List<String> listnew = convertSetToList(jedis.keys("*"));
	for(int i = 0; i<listnew.size(); i++) {
           System.out.println("List of stored keys:: "+listnew.get(i));
        }
   } 
}
