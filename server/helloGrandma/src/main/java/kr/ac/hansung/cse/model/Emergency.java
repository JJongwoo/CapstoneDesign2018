package kr.ac.hansung.cse.model;

import lombok.Getter;
import lombok.Setter;
import lombok.ToString;

@Getter
@Setter
@ToString
public class Emergency {

	String emergency_id;
	String time;
	String date;
	int count_toilet;
	int count_slip;
	int sos;
	int theft;
	
}
