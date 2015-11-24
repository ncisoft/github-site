---
layout: post
styles: [syntax]
title: 软件架构设计的混乱概念
categories: software
tags: ['architecture']
comments: true

---

进入多核时代，软件演进越来越快速，这也带来了一系列的混乱概念，实质上掩盖了软件架构设计能力的不足，试列举如下

* 多核时代，面向对象技术落伍了（如 Java），需要函数式语言才能处理，如 erlang Scala

* 多线程将会导致线程调度竞争，以及无处不在的死锁陷阱，并由此引发一股奇葩的单线程大 Loop
  的推崇风气，以及采用了反人类的大量采用回调技术的 Node.JS日渐风靡
