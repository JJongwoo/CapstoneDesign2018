package kr.ac.hansung.cse.service;

import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.List;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import kr.ac.hansung.cse.dao.EmergencyDao;
import kr.ac.hansung.cse.dao.SensorDataDao;
import kr.ac.hansung.cse.model.Emergency;
import kr.ac.hansung.cse.model.Status;

@Service
public class SensorDataService {

	@Autowired
	private SensorDataDao sensorDataDao;

	@Autowired
	private EmergencyService emergencyService = new EmergencyService();

	private SimpleDateFormat dateFormat = new SimpleDateFormat("yyyy-MM-dd");
	private SimpleDateFormat timeFormat = new SimpleDateFormat("HH:mm:ss");

	private int isTheft = 1;
	private int location_count = 0;
	private int sos_count=0;
	private int bath_count=0;
	private int theft_count=0;
	private Emergency emergency;
	

	public void saveData(String pir1, String pir2, String id, String sona1, String sona2, String btn, String shock) {

		Date currentTime = new Date();
		String date = dateFormat.format(currentTime);
		String time = timeFormat.format(currentTime);
		String datetime = date + " " + time;
		isTheft=1;

		List<Status> status = sensorDataDao.getStatus(10);
		//List<Emergency> emergencies = emergencyService.getEmergency(3);

		// 화장실 초음파가 줄어들고 화장실 적외선이 1이고. 거실 적외선 0이면 체크.
	      if(Integer.parseInt(sona2) < 12 && pir1.equals("0") && pir2.equals("1")) {
	         bath_count++;
	         System.out.println(bath_count);
	      }
	      if(Integer.parseInt(sona2) >= 12 && pir1.equals("1") && pir2.equals("0")) {
	         if(bath_count<3) {// 몇 초 이하는 화장실 이용 체크 안할지 정해야함.
	            bath_count=0;
	         }
	         else if(bath_count>5) { // 몇 초 이상 화장실에 앉아 있을 경우 화장실을 이용했는지 정해야함.
	            // DB 상의 화장실 이용횟수 증가
	            System.out.println("화장실 이용");
	            emergency = new Emergency();
	            emergency.setEmergency_id(id);
	            emergency.setDatetime(datetime);
	            emergency.setTheft(0);
	            emergency.setCount_slip(0);
	            emergency.setCount_toilet(1);
	            emergency.setSos(0);
	            emergencyService.addEmergency(emergency);
	            bath_count=0;
	            
	            //emergencyService.getEmergencyByStatus("count_bath");
	            
	            
	         }
	      }


		// 실내 외출 판정
		String location = status.get(0).getLocation();
		if (location.equals("외출")) {
			if (Integer.parseInt(status.get(2).getSona_living()) < 15) {
				if((status.get(0).getPir_living().equals("1")) 
						|| (status.get(1).getPir_living().equals("1"))){
					System.out.println("들어왔습니당.");
					if(location_count<=0) {
						location = "실내";
						location_count= 2;
					}		
				}
			}
			
			for(int i=0; i<5; i++) {
				if(Integer.parseInt(status.get(i).getSona_living()) < 15 || Integer.parseInt(sona1) < 15)
					isTheft=0;
			}
			// 외출상태에서 집 내부에 생명체 발견
			if (isTheft==1 && theft_count<=0) {
				if (pir1.equals("1") || pir2.equals("1")) {
					// 도둑이얌
					theft_count = 5;
					System.out.println("도둑");
					emergency = new Emergency();
					emergency.setEmergency_id(id);
					emergency.setDatetime(datetime);
					emergency.setTheft(1);
					emergency.setCount_slip(0);
					emergency.setCount_toilet(0);
					emergency.setSos(0);
					emergencyService.addEmergency(emergency);
					
				}
			}

		} else if (location.equals("실내")) {
			if (Integer.parseInt(status.get(3).getSona_living()) < 15) {
				if((status.get(0).getPir_living().equals("0") && status.get(0).getPir_bath().equals("0"))
					|| status.get(1).getPir_living().equals("0") && status.get(1).getPir_bath().equals("0")
					|| status.get(2).getPir_living().equals("0") && status.get(2).getPir_bath().equals("0"))
				{	
					if(location_count<=0) {
						System.out.println("외출");
						location = "외출";
						location_count=2;
					}
				}
			}
			
			/*int l = emergencyService.getEmergencyByStatus("count_toilet");
			if(l >= 3) {
				String [] toilet_first = emergencies.get(2).getDatetime().split(" ")[1].split(":");
				String [] toilet_last = emergencies.get(0).getDatetime().split(" ")[1].split(":");
				System.out.println(toilet_first[2]);
			}*/

		} else
			location = "외출";
		
		

		// SOS버튼 눌렀을때 푸쉬알림
		if (btn.equals("1") && location.equals("실내")) {
			if(sos_count <=0) {
				System.out.println("도와주세요");
				sos_count = 2;
				emergency.setEmergency_id(id);
				emergency.setDatetime(datetime);
				emergency.setTheft(0);
				emergency.setCount_slip(0);
				emergency.setCount_toilet(0);
				emergency.setSos(1);
				emergencyService.addEmergency(emergency);
	
			}
		}

		sensorDataDao.saveData(pir1, pir2, datetime, id, sona1, sona2, btn, location, shock);
		sos_count = sos_count - 1;
		location_count = location_count - 1;
		theft_count -= 1;

	}
}
