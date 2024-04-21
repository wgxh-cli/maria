# `maria` the **Pure FP Language** for **Declarative Animation Rendering**

## Why
Emmm... These following bullshit turned out that, we really need a declarative animation renderer and therefore a language to adapt it

That's why I need it in general. In addition, I want my own language all the time :)

## What
As what the main title said, just yet another **Pure Functional Programming Language**. should be compared with, for example, *Haskell* and so on.
The description above shows that it's a static-typed language.

But what's the difference?

It laid a back door for declarative animation rendering specially. To demonstrate, consider the following example:

```
main_scene = scene ctx skeleton timeline
where
  ctx = (1, "The completeness of real numbers on the real line") // Stand for chapter number, chapter title, respectively
  skeleton =
    <div id="container">
      <div id="title-bar">
        <text id="title-bar-text">{ctx.0} - {ctx.1}</text>
      </div>
      <portal></portal>
      <style>
        .container {
          width: 100%;
          height: 100%;
        }
        .title-bar { width: 100%; height: 5rem; }
        .title-bar-text { font-size: 5rem; }
      </style>
    </div>
  timeline =
    add_portal (<Circle id="circle" radius=10rem stroke=0.3rem />) >>
    create_portal
```

## How
