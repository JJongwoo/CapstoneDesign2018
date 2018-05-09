package kr.ac.hansung.cse.controller;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.net.HttpURLConnection;
import java.net.URL;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpSession;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;

import kr.ac.hansung.cse.service.SensorDataService;

@Controller
public class StatusController {

	@Autowired
	SensorDataService sensorDataService = new SensorDataService();

	@RequestMapping(value = "/savestatus2", method = RequestMethod.POST, produces = { "application/json" })
	public /* Map<String, Object> */String makerepo(@RequestBody Map<String, Object> info) {

		// System.out.println(info);

		sensorDataService.saveData(info.get("dir1Value").toString(), info.get("dir2Value").toString(),
				info.get("id").toString(), info.get("sona1Value").toString(), info.get("sona2Value").toString(),
				info.get("buttonValue").toString());

		return "empty";

	}

	@RequestMapping(value = "/savestatus", method = RequestMethod.GET)
	public String makerepo() {

		// sensorDataService.saveData("31", "50", "jwkim");

		return "home";
	}

	@RequestMapping(value = "/empty")
	public String empty() {

		return "empty";
	}

	@RequestMapping(value = "/mobile/sendFCM")
	public String index(Model model, HttpServletRequest request, HttpSession session/*, MobileTokenVO vo*/)
			throws Exception {

		/*List<MobileTokenVO> tokenList = fcmService.loadFCMInfoList(vo);

		String token = tokenList.get(count).getDEVICE_ID();*/

		final String apiKey = "파이어 베이스의 서버 API키를 여기에 넣는다";
		URL url = new URL("https://fcm.googleapis.com/fcm/send");
		HttpURLConnection conn = (HttpURLConnection) url.openConnection();
		conn.setDoOutput(true);
		conn.setRequestMethod("POST");
		conn.setRequestProperty("Content-Type", "application/json");
		conn.setRequestProperty("Authorization", "key=" + apiKey);

		conn.setDoOutput(true);

		String userId = (String) request.getSession().getAttribute("ssUserId");

		// 이렇게 보내면 주제를 ALL로 지정해놓은 모든 사람들한테 알림을 날려준다.
		String input = "{\"notification\" : {\"title\" : \"여기다 제목 넣기 \", \"body\" : \"여기다 내용 넣기\"}, \"to\":\"/topics/ALL\"}";

		// 이걸로 보내면 특정 토큰을 가지고있는 어플에만 알림을 날려준다 위에 둘중에 한개 골라서 날려주자
		//String input = "{\"notification\" : {\"title\" : \" 여기다 제목넣기 \", \"body\" : \"여기다 내용 넣기\"}, \"to\":\" 여기가 받을 사람 토큰  \"}";

		OutputStream os = conn.getOutputStream();

		// 서버에서 날려서 한글 깨지는 사람은 아래처럼 UTF-8로 인코딩해서 날려주자
		os.write(input.getBytes("UTF-8"));
		os.flush();
		os.close();

		int responseCode = conn.getResponseCode();
		System.out.println("\nSending 'POST' request to URL : " + url);
		System.out.println("Post parameters : " + input);
		System.out.println("Response Code : " + responseCode);

		BufferedReader in = new BufferedReader(new InputStreamReader(conn.getInputStream()));
		String inputLine;
		StringBuffer response = new StringBuffer();

		while ((inputLine = in.readLine()) != null) {
			response.append(inputLine);
		}
		in.close();
		// print result
		System.out.println(response.toString());

		return "jsonView";
	}

}
