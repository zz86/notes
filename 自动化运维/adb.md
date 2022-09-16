
点亮屏幕
```sh
adb shell input keyevent 224
```

截图
```sh
adb exec-out screencap -p > appium/screencap.png
```

滑动屏幕
```sh
adb shell input swipe 550 550 550 1000
```

点击屏幕
```sh
adb shell input tap 990 150
```

打开钉钉
```sh
adb shell am start -n com.alibaba.android.rimet/com.alibaba.android.rimet.biz.LaunchHomeActivity
```

打开钉钉打卡页面
```sh
adb shell am start -a android.intent.action.VIEW -d dingtalk://dingtalkclient/page/link?url=https://attend.dingtalk.com/attend/index.html
```

杀掉钉钉进程
```sh
adb shell am force-stop com.alibaba.android.rimet
```

