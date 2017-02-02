package team4141.robotvision.msee;

import java.util.HashMap;

public interface CSeeHandler {
	void onCSeeInitialized(ICSee csee);
	String getName();
	 HashMap<String, Source>  getSources();
	void onCSeeStopped();
}
