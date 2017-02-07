package team4141.robotvision.msee;



import com.google.gson.Gson;

public class CSee implements Runnable,ICSee {

	static{
		System.loadLibrary("PocoFoundation");
		System.loadLibrary("PocoXML");
		System.loadLibrary("PocoJSON");
		System.loadLibrary("PocoUtil");
		System.loadLibrary("PocoUtil");
		System.loadLibrary("gstreamer-1.0");
//		System.loadLibrary("opencv_world310"); //for windows
		System.loadLibrary("CSee");
	}
	
	private native void init();
	private native  void registerVideoSource(String name,String device,boolean showRaw,String arName,String cvName);
	private native void registerLidarSource(String name,String arName,String cvName);
	public native void start();
	public native void stop();
	public native void switchTo(String channelName);
	public native String[] getChannels();

	private Gson gson = new Gson();
	private boolean isInitialized = false;
	private CSeeHandler handler;
	
	public boolean isInitialized(){return isInitialized;}
	
	public CSee(CSeeHandler handler) {
		this.handler = handler;
	}

	public void onInitialized(){
		handler.onCSeeInitialized(this);
	}


	@Override
	public void run() {
//		discoverSources();
		for(String key  : handler.getSources().keySet()){
			Source source = handler.getSources().get(key);
			if(source instanceof VideoDevice) registerVideoSource(source.getName(),source.getId(),source.showRaw(),source.getARName(),source.getCVName());
			if(source instanceof USBDevice) registerLidarSource(source.getName(),source.getARName(),source.getCVName());
		}
		init();
		String[] channels = getChannels();
		if(channels!=null && channels.length>0){
			for(String channel : channels){
				System.out.printf("channel %s\n",channel);
			}
		}
	}

//	private void init() {
//		isInitialized = true;
//	}
//
//	@Override
//	public synchronized void start() {
//		System.out.println("csee received start.");
//		
//	}
//
//	@Override
//	public void stop() {
//		handler.onCSeeStopped();
//		
//	}

}
