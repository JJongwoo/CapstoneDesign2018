package kr.ac.hansung.cse.service;

import java.util.List;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import kr.ac.hansung.cse.dao.EmergencyDao;
import kr.ac.hansung.cse.model.Emergency;

@Service
public class EmergencyService {

	@Autowired
	private EmergencyDao emergencyDao;

	public void addEmergency(Emergency emergency) {

		emergencyDao.addEmergency(emergency);
	}

	public List<Emergency> viewEmergency(String id) {

		return emergencyDao.viewEmergency(id);
	}
	public int getBathCount(String id) {
		return emergencyDao.getBathCount(id);
	}
	public List<Emergency> getEmergency(int count) {

		return emergencyDao.getEmergency(count);
	}
}
