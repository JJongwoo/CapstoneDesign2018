package kr.ac.hansung.cse.controller;

import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;

@Controller
public class ActivityController {

	@RequestMapping(value = "/activity", method = RequestMethod.GET)
	public String home() {
		
		return "activity";
	}
}
