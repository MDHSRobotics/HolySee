package team4141.robotvision.msee;

import java.util.Hashtable;

public abstract class Source {
	
	protected Hashtable<String,Setting> settings;
	protected String name;
	protected String description;
	protected String id;
	protected Boolean showRaw;
	protected String arName;
	protected String cvName;

	public Source(String id, String description){
		this.id = id;
		this.description = description;
		this.settings = new Hashtable<String,Setting>();
	}
	@Override
	public String toString() {
		return getId();
	}
	public void add(Setting setting) {
		settings.put(setting.getName(), setting);
	}
	public Setting get(String settingName) {
		if(!settings.containsKey(settingName)) return null;
		return settings.get(settingName);
	}
	public String getName(){
		return name;
	}
	public String getARName(){
		return arName;
	}
	public String getCVName(){
		return cvName;
	}
	public String getId() {
		return id;
	}	
	public String getDescription(){
		return description;
	}
	public void setName(String name){
		this.name = name;
	}
	public void setARName(String arName){
		this.arName = arName;
	}
	public void setCVName(String cvName){
		this.cvName = cvName;
	}
	public Boolean showRaw() {
		return showRaw;
	}		
	public void setShowRaw(boolean showRaw) {
		this.showRaw = showRaw;
	}		
}
