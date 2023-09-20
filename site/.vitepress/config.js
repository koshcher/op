import { defineConfig } from "vitepress"

// https://vitepress.dev/reference/site-config
export default defineConfig({
  title: "Кощей Роман: ОП",
  description: "Завдання з основ програмування Кощей Романа ІПЗ-12",

  base: "/op/",
  cleanUrls: true,

  themeConfig: {
    nav: [{ text: "Лабораторні", link: "/labs/1" }],
    sidebar: [
      {
        text: "Лабораторні роботи",
        items: [
          { text: "Спільний код", link: "/labs/shared" },
          { text: "Лабораторна робота №1", link: "/labs/1" },
          { text: "Лабораторна робота №2", link: "/labs/2" },
          { text: "Лабораторна робота №3", link: "/labs/3" },
          // { text: "Лабораторна робота №4", link: "/labs/4" },
          // { text: "Лабораторна робота №5", link: "/labs/5" },
          // { text: "Лабораторна робота №6", link: "/labs/6" },
          // { text: "Лабораторна робота №7", link: "/labs/7" },
          // { text: "Лабораторна робота №8", link: "/labs/8" },
          // { text: "Лабораторна робота №9", link: "/labs/9" },
          // { text: "Лабораторна робота №10", link: "/labs/10" },
          // { text: "Лабораторна робота №11", link: "/labs/11" },
        ],
      },
    ],

    socialLinks: [{ icon: "github", link: "https://github.com/koshcher/op" }],
  },
})
