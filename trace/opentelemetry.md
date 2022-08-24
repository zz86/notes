
- OpenTelemetry的自身定位很明确：数据采集和标准规范的统一，对于数据如何去使用、存储、展示、告警，官方是不涉及的，我们目前推荐使用Prometheus + Grafana做Metrics存储、展示，使用Jaeger做分布式跟踪的存储和展示，使用Fluentd做日志存储和展示。