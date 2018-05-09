package kr.ac.hansung.cse.controller;

import java.util.List;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.RequestMapping;

import kr.ac.hansung.cse.model.User;
import kr.ac.hansung.cse.service.UserService;

@Controller
public class UserController { //controller -> service -> dao

	@Autowired
	private UserService userService;

	@RequestMapping("/users")
	public String getUsers(Model model) {
		
		List<User> users = userService.getUsers();
		model.addAttribute("users", users);
		
		System.out.println(users.get(0));
		
		return "users"; //뷰의 논리적 이름
	}
}
