#include <fstream>
#include "ns3/core-module.h"
#include "ns3/csma-module.h"
#include "ns3/applications-module.h"
#include "ns3/internet-module.h"
#include "ns3/netanim-module.h"

using namespace ns3;

int 
main (int argc, char *argv[])
{
  NS_LOG_COMPONENT_DEFINE("CsmaEchoExample");

  NodeContainer n;
  n.Create (4); // Create 4 nodes

  InternetStackHelper internet;
  internet.Install (n);

  CsmaHelper csma;
  csma.SetChannelAttribute ("DataRate", DataRateValue (DataRate (5000000))); // 5 Mbps
  csma.SetChannelAttribute ("Delay", TimeValue (MilliSeconds (2))); // 2 ms delay
  csma.SetDeviceAttribute ("Mtu", UintegerValue (1400)); // MTU size

  NetDeviceContainer d = csma.Install (n);

  Ipv4AddressHelper ipv4;
  ipv4.SetBase ("10.1.1.0", "255.255.255.0");
  Ipv4InterfaceContainer i = ipv4.Assign (d);

  Ipv4Address serverAddress = i.GetAddress (1);

  uint16_t port = 9;  // Well-known echo port number
  UdpEchoServerHelper server (port);
  ApplicationContainer serverApps = server.Install (n.Get (1)); // Install server on Node 1
  serverApps.Start (Seconds (1.0));
  serverApps.Stop (Seconds (10.0));

  uint32_t packetSize = 1024; // 1024 bytes
  uint32_t maxPacketCount = 1; // Single packet
  Time interPacketInterval = Seconds (1.0); // Interval of 1 second

  UdpEchoClientHelper client (serverAddress, port);
  client.SetAttribute ("MaxPackets", UintegerValue (maxPacketCount));
  client.SetAttribute ("Interval", TimeValue (interPacketInterval));
  client.SetAttribute ("PacketSize", UintegerValue (packetSize));

  ApplicationContainer clientApps = client.Install (n.Get (0)); // Install client on Node 0
  clientApps.Start (Seconds (2.0));
  clientApps.Stop (Seconds (10.0));

  AnimationInterface anim ("second.xml");

  Simulator::Run ();
  Simulator::Destroy ();

  return 0; // Return statement added
}
