<%@ page language="java" contentType="text/html; charset=UTF-8"
	pageEncoding="UTF-8"%>
<%@ taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c"%>


<!--위에 뜨는 메뉴-->
<header>
	<nav class="navbar navbar-expand-md navbar-dark fixed-top bg-dark">
		<a class="navbar-brand" href="#">HelloGrandma</a>
		<button class="navbar-toggler" type="button" data-toggle="collapse"
			data-target="#navbarCollapse" aria-controls="navbarCollapse"
			aria-expanded="false" aria-label="Toggle navigation">
			<span class="navbar-toggler-icon"></span>
		</button>
		<div class="collapse navbar-collapse" id="navbarCollapse">
			<ul class="navbar-nav mr-auto">
				<li class="nav-item active"><a class="nav-link"
					href="<c:url value="/"/>">홈<span class="sr-only">(current)</span></a>
				</li>



				<%-- <li class="nav-item"><a class="nav-link"
					href="<c:url value="/admin"/>">관리자 페이지</a></li> --%>

				<c:if test="${pageContext.request.userPrincipal.name!=null }">
					<li class="nav-item"><a class="nav-link"
						href="<c:url value="/activity"/>">활동</a></li>
					<li class="nav-item"><a class="nav-link" href="#">비상</a></li>
					<li class="nav-item"><a class="nav-link" href="#">주간 보고서</a></li>
					<c:if test="${pageContext.request.userPrincipal.name == 'admin' }">
						<li class="nav-item"><a class="nav-link"
							href="<c:url value="/admin"/>">관리자 페이지</a></li>
					</c:if>

					<%-- 이 메뉴를 선택하면 자동으로 logout이라는 id를 가진 form을 submit함 --%>
					<li class="nav-item"><a class="nav-link"
						href="javascript:document.getElementById('logout').submit()">Logout</a></li>

					<form id="logout" action="<c:url value="logout"/>" method="post">
						<input type="hidden" name="${_csrf.parameterName}"
							value="${_csrf.token}" />
					</form>

				</c:if>



				<c:if test="${pageContext.request.userPrincipal.name==null }">
					<li class="nav-item"><a class="nav-link"
						href="<c:url value="/login"/>">로그인</a></li>
				</c:if>

			</ul>
			<form class="form-inline mt-2 mt-md-0">
				<input class="form-control mr-sm-2" type="text" placeholder="Search"
					aria-label="Search">
				<button class="btn btn-outline-success my-2 my-sm-0" type="submit">Search</button>
			</form>
		</div>
	</nav>
</header>