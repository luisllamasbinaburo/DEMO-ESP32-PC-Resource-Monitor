using NET6_Resource_monitor;
using System.Reactive.Linq;

string brokerIpAddress = "192.168.1.XXX";  //replace with your MQTT broker IP
string networkCardName = "your_network_card_name"; // use SimpleResourceMonitor.printNetworkCards to list card_names

Console.WriteLine("** Starting ***");

Console.Write("  - Initializing simple resource monitor:");
var simpleResourceMonitor = new SimpleResourceMonitor();
simpleResourceMonitor.NetworkCardName = networkCardName;
simpleResourceMonitor.Initialize();
Console.WriteLine(" OK");

Console.Write("  - Initializing MQTT:");
var mqttService = new MqttService();
await mqttService.Initialize(brokerIpAddress);
Console.WriteLine(" OK");

var timer = Observable
               .Interval(TimeSpan.FromSeconds(0.2))
               .Subscribe(async _ =>
               {
				   try
				   {
                       var packet = simpleResourceMonitor.Get();
                       await mqttService.SendMqtt(packet);
                   }
				   catch (Exception ex)
				   {
                       Console.WriteLine($"{DateTime.Now} Error sending: {ex.Message}");                      
				   }
                   
               });

Console.ReadLine();