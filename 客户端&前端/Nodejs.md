#### npm和yarn

- 命令对比

| **npm**                      | **yarn**             |
| ---------------------------- | -------------------- |
| npm install                  | yarn                 |
| npm install react --save     | yarn add react       |
| npm uninstall react --save   | yarn remove react    |
| npm install react --save-dev | yarn add react --dev |
| npm update --save            | yarn upgrade         |
| npm run build                | yarn run build       |

#### npm

- npm i xxx --save-dev 是把依赖写入进devDependencies对象里面
  npm i xxx --save 是把依赖写入进dependencies对象里面
  npm i xxx -g 就是安装到全局下，在命令行的任何地方都可以操作，不会提示“命令不存在等错误”

