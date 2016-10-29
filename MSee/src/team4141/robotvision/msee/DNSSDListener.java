package team4141.robotvision.msee;

import java.io.IOException;
import java.net.InetAddress;
import java.net.UnknownHostException;

import javax.jmdns.JmDNS;
import javax.jmdns.ServiceEvent;
import javax.jmdns.ServiceListener;
import javax.jmdns.ServiceTypeListener;

public class DNSSDListener implements Runnable, ServiceListener, ServiceTypeListener{
	
	public DNSSDListener() {
		System.out.println("DNSSDListener instantiated");
	}

	public void serviceAdded(ServiceEvent event) {
		System.out.println("service added:");
		System.out.println(event.getName());
		System.out.println(event.getType());
		for(String url : event.getInfo().getURLs())
			System.out.println(url);
	}

	public void serviceRemoved(ServiceEvent event) {
		System.out.println("service removed:");
		System.out.println(event.getName());
		System.out.println(event.getType());
		for(String url : event.getInfo().getURLs())
			System.out.println(url);		
	}

	public void serviceResolved(ServiceEvent event) {
		System.out.println("service resolved:");
		System.out.println(event.getName());
		System.out.println(event.getType());
		for(String url : event.getInfo().getURLs())
			System.out.println(url);		
	}
	
	private JmDNS jmdns;

	@Override
	public void run() {
		System.out.println("DNSSDListener run");
		try {
            // Create a JmDNS instance
			for(InetAddress a :InetAddress.getAllByName("localhost")){
				System.out.println(a.toString());
			}
            jmdns = JmDNS.create();

            // Add a service listener
            jmdns.addServiceTypeListener(this);

            // Wait a bit
            Thread.sleep(30000);
        } catch (UnknownHostException e) {
            System.out.println(e.getMessage());
        } catch (IOException e) {
            System.out.println(e.getMessage());
        } catch (InterruptedException e) {
        	System.out.println(e.getMessage());
		}
		
	}

	@Override
	public void serviceTypeAdded(ServiceEvent event) {
		
		//for each service added, spawn a new listener for service providers
		System.out.println("serviceTypeAdded:");
		System.out.println(event.getType());
		this.add(new DNSSDListener(),event.getType());
		
	}

	private void add(ServiceListener listener, String type) {
		jmdns.addServiceListener(type, listener);
	}

	@Override
	public void subTypeForServiceTypeAdded(ServiceEvent event) {

	}

}