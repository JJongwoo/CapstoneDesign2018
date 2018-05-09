package kr.ac.hansung.cse.controller;

import java.util.List;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;

import kr.ac.hansung.cse.model.Emergency;
import kr.ac.hansung.cse.model.User;
import kr.ac.hansung.cse.service.EmergencyService;
import kr.ac.hansung.cse.service.UserService;

@Controller
@RequestMapping("/admin")
public class AdminController {
	
	
	@Autowired
	private UserService userService;
	
	@Autowired
	private EmergencyService emergencyService;
	
	@RequestMapping
	public String adminPage() {
		return "admin";
	}
	
	@RequestMapping("/userManager")
	public String getUsers(Model model) {
		
		List<User> users = userService.getUsers();
		model.addAttribute("users", users);
		
		return "userManager";
	}
	
	@RequestMapping("/userManager/addUser")
	public String addUsers(Model model) {
		User user = new User();
		model.addAttribute("user", user);
		
		return "addUser";
	}
	
	@RequestMapping(value = "/userManager/viewUser/{username}", method=RequestMethod.GET)
	public String viewUser(@PathVariable String username, Model model) {
		
		List<Emergency> emergency = emergencyService.viewEmergency(username);
		model.addAttribute("emergency", emergency);
		System.out.println("메롱");
		
		return "viewEmergency";
	}
}
