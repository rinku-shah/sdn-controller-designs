#include "ue.h"

// Thread function for each UE
void* multithreading_func(void*);

/* High-level functions for various LTE procedures */
bool attach_with_mme(UserEquipment&, Client&, bool, long&);
int send_ue_data(UserEquipment&, int, string, int, int, int, Client&, vector<string>&, int);
vector<string> setup_tunnel(UserEquipment&, Client&, bool, long&);
void detach_ue(UserEquipment&, Client&, int, string, string, string, long&);
void ue_context_release(UserEquipment&, Client&, int, string, string, string, int, bool, long&);
string ue_service_request(UserEquipment&, Client&, int, string, long&);
string network_service_request(UserEquipment&, Client&, int, string);
bool apu_exit(UserEquipment&, Client&);

// Retrieves the starting UE IP address from the controller
string get_starting_IP_Address(UserEquipment&, Client&);

// Generates UE IP addresses and assigns to the network interface
void* multithreading_add_ip(void *);

// Utility function to check if a file already exists
inline bool fileExists (const std::string& );

string GetStdoutFromCommand(string);
