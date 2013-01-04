var AppRouter = Backbone.Router.extend({

  routes: {
    ""                        : "list",
    "collections/page/:page"	: "list",
    "collections/add"         : "addCollection",
    "collections/:id"         : "collectionDetails",
    "about"                   : "about",
    "query"                   : "query",
    "logs"                    : "logs",
    "statistics"              : "statistics",
    "dashboard"               : "dashboard",
    "shell"                   : "shell"
  },
  initialize: function () {
    this.headerView = new HeaderView();
    $('.header').html(this.headerView.el);
  },
  list: function(page) {
    var p = page ? parseInt(page, 10) : 1;
    var wineList = new WineCollection();
    wineList.fetch({
      success: function() {
        $("#content").html(new WineListView({model: wineList, page: p}).el);
      }
    });
    this.headerView.selectMenuItem('collections-menu');
  },
  collectionDetails: function (id) {
    var wine = new Wine({id: id});
    wine.fetch({success: function(){
      $("#content").html(new WineView({model: wine}).el);
    }});
    this.headerView.selectMenuItem();
  },
  addCollection: function() {
    var wine = new Wine();
    $('#content').html(new WineView({model: wine}).el);
    this.headerView.selectMenuItem('add-menu');
  },
  about: function () {
    if (!this.aboutView) {
      this.aboutView = new AboutView();
    }
    $('#content').html(this.aboutView.el);
      this.headerView.selectMenuItem('about-menu');
    },
  query: function () {
    if (!this.queryView) {
      this.queryView = new QueryView();
    }
    $('#content').html(this.queryView.el);
      this.headerView.selectMenuItem('query-menu');
      initQuery();
    },
  shell: function () {
    if (!this.shellView) {
      this.shellView = new ShellView();
    }
    $('#content').html(this.shellView.el);
      this.headerView.selectMenuItem('shell-menu');
      initShell();
    },
  logs: function () {
    if (!this.logsView) {
      this.logsView = new LogsView();
    }
    $('#content').html(this.logsView.el);
      this.headerView.selectMenuItem('logs-menu');
    },
  statistics: function () {
    if (!this.statisticsView) {
      this.statisticsView = new StatisticsView();
    }
    $('#content').html(this.statisticsView.el);
      this.headerView.selectMenuItem('statistics-menu');
    },
  dashboard: function () {
    if (!this.dashboardView) {
      this.dashboardView = new DashboardView();
    }
    $('#content').html(this.dashboardView.el);
      this.headerView.selectMenuItem('dashboard-menu');
    }
});

utils.loadTemplate(['HeaderView', 'WineView', 'WineListItemView', 'AboutView', 'QueryView', 'ShellView', 'StatisticsView', 'LogsView', 'DashboardView'], function() {
    app = new AppRouter();
    Backbone.history.start();
});
