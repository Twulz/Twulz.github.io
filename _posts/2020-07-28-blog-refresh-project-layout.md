---
layout: post
title:  "Refreshing this Blog - Category and Project Layouts"
date:   2020-07-28
categories: Things Software Blog
tags: Jekyll Blog Github-Pages Bootstrap
---

In this post I build the “Project" and "Category" page layout, fix the post categories and finalise Stage 1 of my new refreshed blog using Bootstrap 4, Jekyll and GitHub Pages. 

<!--more-->
## Project Pages, Categories and Breadcrumbs

### Breadcrumbs

I'd decided that I want breadcrumbs across the majority of my site, except for the homepage, but this also meant a complete overhaul to the way I had categorised all my posts. There was a _lot_ of back-and-forth deciding how exactly I wanted these to look but here I've just skipped to the final design.

![Header and Breadcrumbs](/images/blog/breadcrumbs.png)

I settled on having the categories as links which would be easily configurable from the post metadata. All posts start with "Things" (with other non-post pages neglecting this category) and then the category of the "Thing" which currently is: Mechatronics, Software, Miniature, Garden and then finally the project (or "Other"). This way, the breadcrumbs start with "Home" then iterate over the categories of the post to create the breadcrumbs.

This change meant I had to go back and fix all of my previous posts to fit this format, and I made some adjustments to align some of the tags too. After all, what's an overhaul without changing _everything_?

Example page metadata with the new categories:
```md
---
layout: post
title:  "Refreshing this Blog - Category and Project Layouts"
date:   2020-07-28
categories: Things Software Blog
tags: Jekyll Blog Github-Pages Bootstrap
---
```

And the breadcrumbs component:
###### breadcrumbs.html
```html
<nav aria-label="breadcrumb">
    <ol class="breadcrumb">
        <li class="breadcrumb-item"><a href="/">Home</a></li>
        {% raw %}{% if page.categories %}
            {% assign url = site.url %}
            {% for category in page.categories %}
                {% assign url = url | append: "/" %}
                {% assign url = url | append: category %}{% endraw %}
                <li class="breadcrumb-item">
                    <a href="{% raw %}{{ url }}{% endraw %}">
                        {% raw %}{{ category }}{% endraw %}
                    </a>
                </li>
            {% raw %}{% endfor %}
        {% endif %}
        {% if page.breadcrumbs %}
            {% assign url = site.url %}
            {% for breadcrumb in page.breadcrumbs %}
                {% assign url = url | append: "/" %}
                {% assign url = url | append: breadcrumb %}{% endraw %}
                <li class="breadcrumb-item">
                    <a href="{% raw %}{{ url }}{% endraw %}">
                        {% raw %}{{ breadcrumb }}{% endraw %}
                    </a>
                </li>
            {% raw %}{% endfor %}
        {% endif %}{% endraw %}
        <li class="breadcrumb-item active" aria-current="page">{% raw %}{{ page.title }}{% endraw %}</li>
    </ol>
</nav>
```

### Category Layout

In the previous website I hadn't used Jekyll to create a category or project page so here I took apart one of the copy/pasted HTML pages and converted it to a parameterised page that I could fill out with markdown and metadata instead of repeating HTML.

I ended up with quite a bit of metadata needed for each category page; I defined the categories as the "Things": Mechatronics Things, Software Things, Mini Things and Garden Things. I gave the option of a hero image or defining the projects to be featured on a carousel. 

###### mechatronics.md
```md
---
layout: category
group: Mechatronics
title:  Mechatronics Things
projects:
    donkeycar: "Basil Faulty the DonkeyCar"
    fyp: "My Final Year Projects"
    orrery: "An Orrery: Model of the Solar System"
    printer: "A Prusa i3 MK2 3D Printer"
    cube4x4x4: "A 4x4x4 LED Cube"
    otherMecha: "Other Mechatronics Things"
hero_image: 
    path: /images/pickAndPlace/11_complete_setup.jpg
    alt: Mechatronics Things
carousel_images:
- path: /images/donkeyCar/buildDay/06_basil.jpg
  alt: Basil Faulty the Autonomous DonkeyCar
  active: active
  link: /things/mechatronics/donkeycar/
- path: /images/mechatronicsFYP/10_package_box.jpg
  alt: Package Box for my Final Year Project
  link: /things/mechatronics/fyp/
- path: /images/orrery/finished_04.jpg
  alt: "Orrery: A model of the Planets"
  link: /things/mechatronics/orrery/
breadcrumbs: 
- Things
---
```

There's also the basic list of projects below like in the old design; I'd like to redo this part shortly but I think I just ran out of steam for now! Here is the current version of the category layout:

###### category.html
```html
---
layout: default
---
{% raw %}{% assign carousel_number = page.carousel_images.size | minus: 1 %}{% endraw %}

<div class="col-xl-8 col-lg-9">

	{% raw %}{% include breadcrumbs.html %}{% endraw %}

	<article>

		<h1>
			{% raw %}{{ page.title }}{% endraw %}
		</h1>

		<div id="carouselExampleIndicators" class="carousel slide py-2" data-ride="carousel">
			<ol class="carousel-indicators">
				{% raw %}{% for i in (0..carousel_number) %}
					{% if i == 0 %}
						{% assign active = 'active' %}
					{% endif %}{% endraw %}
					<li data-target="#carouselExampleIndicators" data-slide-to="{% raw %}{{ i }}{% endraw %}" class="{% raw %}{{ active }}{% endraw %}"></li>
				{% raw %}{% endfor %}{% endraw %}
			</ol>
			<div class="carousel-inner">
				{% raw %}{% for image in page.carousel_images %}{% endraw %}
					<div class="carousel-item {% raw %}{{ image.active }}{% endraw %}">
						<img class="d-block w-100" src="{% raw %}{{ site.baseurl }}{{ image.path }}{% endraw %}" alt="{% raw %}{{ image.alt }}{% endraw %}">
						<div class="carousel-caption d-none d-md-block">
							<a class="white-text" href="{% raw %}{{ site.baseurl }}{{image.link }}{% endraw %}" alt="{% raw %}{{ image.alt }}{% endraw %}">
								<h3>{% raw %}{{ image.alt }}{% endraw %}</h3>
							</a>
						</div>
					</div>
				{% raw %}{% endfor %}{% endraw %}
			</div>
			<a class="carousel-control-prev" href="#carouselExampleIndicators" role="button" data-slide="prev">
			  <span class="carousel-control-prev-icon" aria-hidden="true"></span>
			  <span class="sr-only">Previous</span>
			</a>
			<a class="carousel-control-next" href="#carouselExampleIndicators" role="button" data-slide="next">
			  <span class="carousel-control-next-icon" aria-hidden="true"></span>
			  <span class="sr-only">Next</span>
			</a>
		</div>

		<div class="pt-2 page-content">
			{% raw %}{{ content }}{% endraw %}
		</div>
		
		<div class="pt-6">
			<h2>{% raw %}{{ page.posts_title }}{% endraw %}</h2>
		</div>
		
		<div class="pt-2">
			<ul>
				{% raw %}{% for project in page.projects %}{% endraw %}
					<li><h4>
						<a href="{% raw %}{{ site.baseurl }}{% endraw %}/things/{% raw %}{{ page.group }}{% endraw %}/{% raw %}{{ project[0] }}{% endraw %}">
							{% raw %}{{ project[1] }}{% endraw %}
						</a>
					</h4>
					<p class="pDate">{% raw %}{{ post.date | date: '%B %d, %Y' }}{% endraw %}</p>
					<p>{% raw %}{{ post.excerpt }}{% endraw %}</p></li>
				{% raw %}{% endfor %}{% endraw %}
			</ul>
		</div>

	</article>
</div>
```

Done! This layout also inherits from the default layout so it's got all of the header, footer, navbar and asides that I'd developed previously.

![Mechatronics Category Page](/images/blog/mechatronics_things.png)

### Project Layout

I also had to parameterise the project layout from all its repeated code. The project layout is slightly different to the category in that I don't use the carousel - just a hero image. I still added a fair few configurable fields though:

###### donkeycar.md
```md
---
layout: project
group: Mechatronics
title: Basil Faulty the DonkeyCar
hero_image: 
    path: /images/donkeyCar/setup/05_basil.jpg
    alt: Basil Faulty the DonkeyCar
posts_title: "Here are the posts I have made so far about Basil Faulty the DonkeyCar:"
category: DonkeyCar
breadcrumbs: 
- Things
- Mechatronics
---
```

And finally the html with jekyll/liquid tags:

###### project.html
```html
---
layout: general
---

{% raw %}{% assign carousel_number = page.carousel_images.size | minus: 1 %}{% endraw %}

<div class="pt-2">
    <p>{% raw %}{{ page.description }}{% endraw %}</p>
</div>

<div class="hero-image">
    <img src="{% raw %}{{ site.baseurl}}{{ page.hero_image.path }}{% endraw %}" alt="{% raw %}{{ page.hero_image.alt }}{% endraw %}" />
</div>

<div class="pt-2 page-content">
    {% raw %}{{ content }}{% endraw %}
</div>

<div class="pt-6">
    <h2>{% raw %}{{ page.posts_title }}{% endraw %}</h2>
</div>

<div class="pt-2">
    {% raw %}{% for post in site.categories[page.category] reversed %}{% endraw %}
        <h4>
            <a href="{% raw %}{{ post.url }}{% endraw %}">
                {% raw %}{{ post.title }}{% endraw %}
            </a>
        </h4>
        <p class="pDate">{% raw %}{{ post.date | date: '%B %d, %Y' }}{% endraw %}</p>
        <p>{% raw %}{{ post.excerpt }}{% endraw %}</p>
    {% raw %}{% endfor %}{% endraw %}
</div>
```

And here is the finalised project page, again utilising many of the previous components I'd developed:

![DonkeyCar Project Page](/images/blog/donkeycar_page.png)

I think I'm finally done for the Blog refresh! I made a new Blog using Jekyll, Bootstrap and GitHub Pages!