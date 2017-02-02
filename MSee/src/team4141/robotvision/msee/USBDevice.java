package team4141.robotvision.msee;

public class USBDevice extends Source{

	public String getDevice() {
		return getId();
	}

	public USBDevice(String device, String description) {
		super(device,description);
	}


	@Override
	public String toString() {
		StringBuilder sb = new StringBuilder();
		sb.append("{");
		if(getId()!=null){
			if(sb.length()>1) sb.append(",");
			sb.append("\"id\":\"");
			sb.append(getId());
			sb.append("\"");
		}
		if(getName()!=null){
			if(sb.length()>1) sb.append(",");
			sb.append("\"name\":\"");
			sb.append(getName());
			sb.append("\"");
		}
		if(getDescription()!=null){
			if(sb.length()>1) sb.append(",");
			sb.append("\"description\":\"");
			sb.append(getDescription());
			sb.append("\"");
		}
		if(showRaw()!=null){
			if(sb.length()>1) sb.append(",");
			sb.append("\"showRaw\":");
			sb.append(showRaw.booleanValue());
		}
		if(getARName()!=null){
			if(sb.length()>1) sb.append(",");
			sb.append("\"arName\":\"");
			sb.append(getARName());
			sb.append("\"");
		}
		if(getCVName()!=null){
			if(sb.length()>1) sb.append(",");
			sb.append("\"cvName\":\"");
			sb.append(getCVName());
			sb.append("\"");
		}
		if(settings!=null && settings.size()>0){
			if(sb.length()>1) sb.append(",");
			sb.append("\"settings\":[");
			boolean isFirst = true;
			for(String settingName : settings.keySet()){
				if(isFirst) isFirst = false;
				else sb.append(",");
				sb.append(settings.get(settingName).toString());
			}
			sb.append("]");
			
		}
		sb.append("}");
		
		return sb.toString();
	}
}
