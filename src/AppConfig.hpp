//
// Created by Touka on 2024/1/10.
//

#ifndef APPCONFIG_HPP
#define APPCONFIG_HPP
#include <QtWidgets/QMenu>
#include <QSystemTrayIcon>
#include <memory>

namespace AppConfig {
  static std::shared_ptr<QSystemTrayIcon> getTrayIcon() {
    static const auto trayIcon = std::make_shared<QSystemTrayIcon>(QIcon(":/icon/resource/icon/calendar_month.svg"));
    return trayIcon;
  }

  constexpr static std::string_view appName() {
    return "Schedule";
  }

}

#endif //APPCONFIG_HPP
