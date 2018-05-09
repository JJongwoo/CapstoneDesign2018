package kr.ac.hansung.cse.model;

import lombok.Getter;
import lombok.Setter;
import lombok.ToString;

@Setter
@Getter
@ToString
public class User {
	
	private String username;
	private String password;
	private int enabled;
	private String name;
	private String phone;
	private String address;
	
}
