package team4141.robotvision.msee;

import org.usfirst.frc.team4141.MDRobotBase.config.IntegerConfigSetting;
import org.usfirst.frc.team4141.MDRobotBase.config.StringConfigSetting;

public class Main {

	public static void main(String[] args) {
		System.out.println("starting MSee server ... ");
//		Server server = new Server();
//		server
//			.add("frameRate", new IntegerConfigSetting(new Integer(1), new Integer(30), new Integer(20)))
//			.add("serverName", new StringConfigSetting("HolySee"))
//			.configure();
//		server.start();

//	    new Thread(new RoboRioListener()) .start();
	    
//		while(server.isRunning()){
//		boolean done = false;
//		while(!done){
//			try {
//				Thread.sleep(100);
//			} catch (InterruptedException e) {
//				
//			}
//		}
		
		CSee csee = new CSee();
		
		System.out.println("MSee server shutting down ... ");
	}

}
