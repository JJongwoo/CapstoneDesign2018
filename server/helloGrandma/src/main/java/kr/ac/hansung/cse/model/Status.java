package kr.ac.hansung.cse.model;

import lombok.Getter;
import lombok.Setter;
import lombok.ToString;

@Getter
@Setter
@ToString
public class Status {
	
	String sensor_id;
	String pir_living;
	String pir_bath;
	String sona_living;
	String sona_bath;
	String sos;
	String time;
	String date;
	String location;

}
