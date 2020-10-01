---
layout: post
title:  "Refreshing this Blog - Home Page Layout"
date:   2020-07-14
categories: Things Software Blog
tags: Jekyll Blog Github-Pages Bootstrap
---

In this post I build the "Home page" layout for my new refreshed blog using Bootstrap 4, Jekyll and GitHub Pages.

<!--more-->

## Homepage Layout

I'm recreating the same home page that I had on the old blog with the grid of posts that you could flick back through to browse all the posts with their blurbs and (in some cases) pictures.

I used the `default` layout from the previous posts which included the header, navbar and asides already so I just needed to add the content to the main container.

The jumbotron was pretty much straight out-of-the-box so I'll just include the code below.

The grid of posts was using the card modules similar to the asides from the previous post but I decided it looked much better without the background for these ones. I had to experiment a lot with the margin and padding utility classes before they all looked nice.


###### index.html
```html
---
layout: default
group: Blog
title: Home
---
<div class="col-xl-8 col-lg-9 mt-2">
{% raw %}{% include libs/truncate_start %}
{% for post in paginator.posts limit: 1 %}{% endraw %}
	<!-- Featured Article -->
	<div class="jumbotron py-4">
		<h1 class="display-4"><a href="{% raw %}{{ site.baseurl }}{{ post.url }}{% endraw %}">{% raw %}{{ post.title }}{% endraw %}</a></h1>
		<p class="lead">
			<time datetime="{% raw %}{{ post.date | date_to_xmlschema }}{% endraw %}">{% raw %}{{ post.date | date: site.date_format }}{% endraw %}</time>
		</p>
		<hr class="my-4">
		<img src="{% raw %}{{ site.baseurl }}{{ post.related_image.path }}{% endraw %}" alt="{% raw %}{{ post.related_image.alt }}{% endraw %}" />
		<p>
			{% raw %}{% include libs/thumbnail %}
			{% comment %} {% include libs/truncate_exec %} {% endcomment %} 
			{{ post.excerpt }}{% endraw %}
		</p>
		<a class="btn btn-primary btn-lg" href="{% raw %}{{ site.baseurl }}{{ post.url }}{% endraw %}" role="button">Read This &raquo;</a>
	</div>
{% raw %}{% endfor %}
{% assign m = 0 %}
{% capture n %}{{ site.paginate | minus: 1 }}{% endcapture %}
{% for post in paginator.posts limit: n offset: 1 %}
	{% if m == 0 %}{% endraw %}
		<!-- Followed Articles -->
		<div class="row">
	{% raw %}{% endif %}{% endraw %}
			<div class="col-sm-6 col-md-4 my-1">
				{% raw %}{% include libs/thumbnail %}{% endraw %}
				<h4>
					<a href="{% raw %}{{ site.baseurl }}{{ post.url }}{% endraw %}">{% raw %}{{ post.title }}{% endraw %}</a>
				</h4>
				<h5>
					<time datetime="{% raw %}{{ post.date | date_to_xmlschema }}{% endraw %}">{% raw %}{{ post.date | date: site.date_format }}{% endraw %}</time>
				</h5>
				<div class="card-image">
					<img src="{% raw %}{{ site.baseurl }}{{ post.related_image.path }}{% endraw %}" alt="{% raw %}{{ post.related_image.alt }}{% endraw %}" />
				</div>
				<div class="content">
					{% raw %}{{ post.excerpt }}{% endraw %}
				</div>
				<a class="btn btn-secondary btn-sm" href="{% raw %}{{ site.baseurl }}{{ post.url }}{% endraw %}" class="btn">Read this &raquo;</a>
			</div>
	{% raw %}{% capture m %}{{ m | plus: 1 }}{% endcapture %}
	{% if forloop.last %}{% endraw %}
		</div><!--/row-fluid-->
		{% raw %}{% assign m = 0 %}
	{% endif %}
{% endfor %}
{% include libs/truncate_end %}
{% include pagenation.html %}{% endraw %}
<hr class="d-lg-none" />
</div>
```

And done! Things are starting to look a _lot_ better:

![Homepage screenshot](/images/blog/homepage.png)