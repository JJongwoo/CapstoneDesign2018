<%@ page language="java" contentType="text/html; charset=UTF-8"
	pageEncoding="UTF-8"%>
<%@ taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c"%>


<div id="myCarousel" class="carousel slide" data-ride="carousel">
	<ol class="carousel-indicators">
		<li data-target="#myCarousel" data-slide-to="0" class="active"></li>
		<li data-target="#myCarousel" data-slide-to="1"></li>
	</ol>
	<div class="carousel-inner">
		<div class="carousel-item active">
			<img class="first-slide"
				src="<c:url value="resources/image/main_visual2.jpg"/>"
				alt="First slide"
				class = "img-responsive">
			<div class="container">
				<div class="carousel-caption text-left" style="color: black;">
					<h1>Hello GrandMa!</h1>
					<p>최고의 고독사 예방 시스템</p>
					<p>
						<a class="btn btn-lg btn-primary" href="#" role="button">지금
							가입하러 가기!</a>
					</p>
				</div>
			</div>
		</div>
		<div class="carousel-item">
			<img class="second-slide"
				src="<c:url value="resources/image/main_visual3.jpg"/>"
				alt="Second slide"
				class = "img-responsive">
			<div class="container">
				<div class="carousel-caption text-left">
					<h1>엄마 요즘 잘 지내지?</h1>
					<p>24시간 부모님을 지켜드리는 지킴이</p>
					<p>
						<a class="btn btn-lg btn-primary" href="#" role="button">더 많은
							정보를 원한다면</a>
					</p>
				</div>
			</div>
		</div>
	</div>
	<a class="carousel-control-prev" href="#myCarousel" role="button"
		data-slide="prev"> <span class="carousel-control-prev-icon"
		aria-hidden="true"></span> <span class="sr-only">Previous</span>
	</a> <a class="carousel-control-next" href="#myCarousel" role="button"
		data-slide="next"> <span class="carousel-control-next-icon"
		aria-hidden="true"></span> <span class="sr-only">Next</span>
	</a>
</div>


<!-- Marketing messaging and featurettes
      ================================================== --> <!-- Wrap the rest of the page in another container to center all the content. -->

<div class="container marketing">

	<!-- Three columns of text below the carousel -->
	<div class="row">
		<div class="col-lg-4">
			<img class="rounded-circle"
				src="data:image/gif;base64,R0lGODlhAQABAIAAAHd3dwAAACH5BAAAAAAALAAAAAABAAEAAAICRAEAOw=="
				alt="Generic placeholder image" width="140" height="140">
			<h2>Heading</h2>
			<p>Donec sed odio dui. Etiam porta sem malesuada magna mollis
				euismod. Nullam id dolor id nibh ultricies vehicula ut id elit.
				Morbi leo risus, porta ac consectetur ac, vestibulum at eros.
				Praesent commodo cursus magna.</p>
			<p>
				<a class="btn btn-secondary" href="#" role="button">View details
					&raquo;</a>
			</p>
		</div>
		<!-- /.col-lg-4 -->
		<div class="col-lg-4">
			<img class="rounded-circle"
				src="data:image/gif;base64,R0lGODlhAQABAIAAAHd3dwAAACH5BAAAAAAALAAAAAABAAEAAAICRAEAOw=="
				alt="Generic placeholder image" width="140" height="140">
			<h2>Heading</h2>
			<p>Duis mollis, est non commodo luctus, nisi erat porttitor
				ligula, eget lacinia odio sem nec elit. Cras mattis consectetur
				purus sit amet fermentum. Fusce dapibus, tellus ac cursus commodo,
				tortor mauris condimentum nibh.</p>
			<p>
				<a class="btn btn-secondary" href="#" role="button">View details
					&raquo;</a>
			</p>
		</div>
		<!-- /.col-lg-4 -->
		<div class="col-lg-4">
			<img class="rounded-circle"
				src="data:image/gif;base64,R0lGODlhAQABAIAAAHd3dwAAACH5BAAAAAAALAAAAAABAAEAAAICRAEAOw=="
				alt="Generic placeholder image" width="140" height="140">
			<h2>Heading</h2>
			<p>Donec sed odio dui. Cras justo odio, dapibus ac facilisis in,
				egestas eget quam. Vestibulum id ligula porta felis euismod semper.
				Fusce dapibus, tellus ac cursus commodo, tortor mauris condimentum
				nibh, ut fermentum massa justo sit amet risus.</p>
			<p>
				<a class="btn btn-secondary" href="#" role="button">View details
					&raquo;</a>
			</p>
		</div>
		<!-- /.col-lg-4 -->
	</div>
	<!-- /.row -->
</div>
<!-- /.container -->