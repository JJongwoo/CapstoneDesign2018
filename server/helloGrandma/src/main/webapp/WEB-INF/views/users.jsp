<%@ page language="java" contentType="text/html; charset=UTF-8"
	pageEncoding="UTF-8"%>
<%@ taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c"%>

<div class="container-wrapper">
	<div class="container">
		<h2>All Users</h2>
		<p>고객 명단</p>
		<table class="table table-striped">
			<thead>
				<tr class="bg-warning">
					<th>User_ID</th>
					<th>Password</th>
					<th>Enabled</th>
					<th>Name</th>
					<th>Phone</th>
					<th>Address</th>
				</tr>
			</thead>
			<tbody>
				<c:forEach var="user" items="${users}">
					<!-- items값과  Contoller의 키값과 일치해야함 -->
					<tr>
						<td>${user.username}</td>
						<td>${user.password}</td>
						<td>${user.enabled}</td>
						<td>${user.name}</td>
						<td>${user.phone}</td>
						<td>${user.address}</td>
						</td>
					</tr>
				</c:forEach>
			</tbody>
		</table>
	</div>
</div>

