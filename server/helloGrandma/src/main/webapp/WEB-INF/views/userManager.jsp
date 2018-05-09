<%@ page language="java" contentType="text/html; charset=UTF-8"
	pageEncoding="UTF-8"%>
<%@ taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c"%>

<div class="container-wrapper">
	<div class="container">
		<h2>고객 정보 관리</h2>
		<p>고객 현황</p>
		<table class="table table-striped">
			<thead>
				<tr class="bg-warning">
					<th>User_ID</th>
					<th>Phone</th>
					<th>Address</th>
					<th>Name</th>
					<th></th>
				</tr>
			</thead>
			<tbody>
				<c:forEach var="user" items="${users}">
					<!-- items값과  Contoller의 키값과 일치해야함 -->
					<tr>
						<td>${user.username}</td>
						<td>${user.phone}</td>
						<td>${user.address}</td>
						<td>${user.name}</td>
						<td><a href="<c:url value="/admin/userManager/viewUser/${user.username}"/>">
							<i class="fa fa-info-circle"></i></a>
					</tr>
				</c:forEach>
			</tbody>
		</table>
		
		<a href="<c:url value="/admin/userManager/addUser"/>" class="btn btn-primary"> Add User</a>
	</div>
</div>

