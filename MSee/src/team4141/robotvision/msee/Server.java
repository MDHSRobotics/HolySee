package team4141.robotvision.msee;

import java.net.Inet4Address;
import java.net.URI;
import java.util.Hashtable;
import java.util.Map;
import java.util.concurrent.Executors;
import java.util.concurrent.ScheduledExecutorService;
import java.util.concurrent.TimeUnit;

import org.eclipse.jetty.websocket.client.ClientUpgradeRequest;
import org.eclipse.jetty.websocket.client.WebSocketClient;
import org.usfirst.frc.team4141.MDRobotBase.config.ConfigSetting;
import org.usfirst.frc.team4141.MDRobotBase.eventmanager.ClientSocket;
import org.usfirst.frc.team4141.MDRobotBase.eventmanager.Dispatcher;
import org.usfirst.frc.team4141.MDRobotBase.eventmanager.EventManager;
import org.usfirst.frc.team4141.MDRobotBase.eventmanager.JSON;
import org.usfirst.frc.team4141.MDRobotBase.eventmanager.LogNotification;
import org.usfirst.frc.team4141.MDRobotBase.eventmanager.MessageHandler;

public class Server implements MessageHandler{

	private EventManager eventManager;
	private boolean isRunning;
	private ScheduledExecutorService messageProcessorsPool;
	private Hashtable<String, ConfigSetting> settings;

	public Server() {
		this.eventManager = new EventManager(this,true);
		isRunning = false;
		messageProcessorsPool = Executors.newScheduledThreadPool(4);
		settings = new Hashtable<String, ConfigSetting>();
	}

	public void process(String messageText) {
//		System.out.println("Robot received message: "+messageText);
		Map message = JSON.parse(messageText);
		System.out.println("received message: "+messageText);
		
		if(message.containsKey("type")){
			String type = message.get("type").toString();
//			if(type.equals("consoleButtonUpdate")){
//				updateConsoleOIButton(message);
//			}
			if(type.equals("settingUpdate")){
				updateSetting(message);
			}
		}
	}
	
	private void updateSetting(Map message) {
		//format: {"type":"settingUpdate", "subsystem":"core", "settingName":"autoCommand", "value":"AutonomousCommand2"}
		//we already know that it's a settingUpdate
		//do 2 things:
		//1. get setting from core and update it.
		//2. update preferences
		if(message.containsKey("settingName")){
			String settingName = (String)(message.get("settingName"));
			if(settings.containsKey(settingName)){
				ConfigSetting setting = settings.get(settingName);
				System.out.println("updating setting "+setting.getName());
				if(message.containsKey("value")){
					setting.setValue(message.get("value"));
					System.out.println("value now set to "+setting.getValue().toString());
				}
				if(message.containsKey("min")){
					setting.setMin(message.get("min"));
					System.out.println("min now set to "+setting.getMin().toString());
				}
				if(message.containsKey("max")){
					setting.setMax(message.get("max"));
					System.out.println("max now set to "+setting.getMax().toString());
				}
			}
		}
		
	}	
	
	public void start(){
		try {
			this.eventManager.start();
			messageProcessorsPool.scheduleAtFixedRate(new Dispatcher(eventManager),10,100,TimeUnit.MILLISECONDS);
			isRunning = true;
		} catch (Exception e) {
			// TODO Auto-generated catch block
			System.out.println("unable to start web socket manager");
			e.printStackTrace();		}
	}
	
	public void connect() {
		eventManager.post(new LogNotification(LogNotification.Level.INFO, "Server.connect()", "server received client connection"));
		eventManager.post(new ConfigurationNotification(this));
	}

	public boolean isRunning() {
		return isRunning;
	}

	public Hashtable<String, ConfigSetting> getSettings() {
		// TODO Auto-generated method stub
		return settings;
	}

	public Server add(String name, ConfigSetting setting) {
		setting.setName(name);
		settings.put(name, setting);
		return this;
	}

	public void configure() {
	}

	public void connect(String serviceName, Inet4Address address, int port) {
		System.out.println("-->"+address+"<--");
        String destUri = "ws:/"+address+":"+port;


        ClientSocket clientSocket = new ClientSocket();
        WebSocketClient client = new WebSocketClient();

        try
        {
            client.start();

            URI uri = new URI(destUri);
            System.out.println("connecting to :"+destUri);
            client.connect(clientSocket,uri);
            System.out.printf("Connecting to : %s%n",uri);

           
        }
        catch (Throwable t)
        {
        	System.out.println("some error occured");
            t.printStackTrace();
        }
		
	}
}
