paste ../stats_1.csv ../stats_2.csv ../stats_3.csv ../stats_4.csv |tr -s "," " "|tr -s [:blank:] " " > tmp
cat tmp | tail -n +2 > tmp_stats
echo "#UE Throughput Delay(ms)  SR-Delay(ms)" > ../results/tpt_delay.dat
awk -f compile_tpt_delay.awk tmp_stats >> ../results/tpt_delay.dat

#echo "#UE RootTraffic(NoOfPackets)" > ../results/traffic_in_pkts.dat
# paste ../packet_in_1.dat ../packet_in_2.dat ../packet_in_3.dat ../packet_in_4.dat ../packet_in_5.dat ../packet_in_6.dat |tr -s "," " "|tr -s [:blank:] " " > tmp_pkt
#cat tmp_pkt| cut -d " " -f 1,2,7,12,17,22,27| awk '{print $1, $2+$3+$4+$5+$6+$7}' >> ../results/traffic_in_pkts.dat

#echo "#UE Tx(Mbps) Rx(Mbps) Total(Mbps)" > ../results/bandwidth.dat
#cat ../bandwidth_1.dat > tmp
#cat tmp | tail -n +2 > tmp_bw
#cat tmp_bw | awk 'BEGIN{FS = ","}{print $1, $2*1000,  $3*1000,  $4*1000}' >> ../results/bandwidth.dat

