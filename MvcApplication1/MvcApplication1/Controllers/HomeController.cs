﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;
using Wrapper;
using System.IO;
using System.Globalization;
using System.Net;


namespace MvcApplication1.Controllers
{
    public class HomeController : Controller
    {

        DateTime[] holidays = new DateTime[]{
           /*******2015******/
            new DateTime(2015,11,11),
            new DateTime(2015,12,25),
           /*******2016******/
           new DateTime(2016,1,1),
           new DateTime(2016,3,28),
           new DateTime(2016,5,16),
           new DateTime(2016,7,14),
           new DateTime(2016,8,15),
           new DateTime(2016,11,1),
           new DateTime(2016,11,11),
           /*******2017******/
           new DateTime(2017,4,17),
           new DateTime(2017,5,1),
           new DateTime(2017,5,8),
           new DateTime(2017,5,25),
           new DateTime(2017,6,5),
           new DateTime(2017,7,14),
           new DateTime(2017,8,15),
           new DateTime(2017,11,1),
           new DateTime(2017,12,25),
           /*******2018******/
           new DateTime(2018,1,1),
           new DateTime(2018,4,2),
           new DateTime(2018,5,1),
           new DateTime(2018,5,8),
           new DateTime(2018,5,10),
           new DateTime(2018,5,21),
           new DateTime(2018,8,15),
           new DateTime(2018,11,1),
           new DateTime(2018,12,25),
           /*******2019******/
           new DateTime(2019,1,1),
           new DateTime(2019,4,22),
           new DateTime(2019,5,1),
           new DateTime(2019,5,8),
           new DateTime(2019,5,30),
           new DateTime(2019,6,10),
           new DateTime(2019,8,15),
           new DateTime(2019,11,1),
           new DateTime(2019,11,11),
           new DateTime(2019,12,25),
           /*******2020******/
           new DateTime(2020,1,1),
           new DateTime(2020,4,13),
           new DateTime(2020,5,1),
           new DateTime(2020,5,8),
           new DateTime(2020,5,21),
           new DateTime(2020,6,1),
           new DateTime(2020,7,14),
           new DateTime(2020,11,11),
           new DateTime(2020,12,25),
           /*******2021******/
           new DateTime(2021,1,1),
           new DateTime(2021,4,5),
           new DateTime(2021,5,13),
           new DateTime(2021,5,24),
           new DateTime(2021,7,14),
           new DateTime(2021,11,1),
           new DateTime(2021,11,11),
        };


        Dictionary<string, int> stocks = new Dictionary<string, int>()
        {
            {"EuroStoxx500",1},
            {"FTSE100",2},
            {"SP500",3},
            {"HangSeng",4},
            {"Nikkei225",5},
            {"SPASX200",6},
            {"GBPEUR",7},
            {"USDEUR",8},
            {"HKDEUR",9},
            {"JPYEUR",10},
            {"AUDEUR",11}
        };

        Dictionary<string, int> backtest = new Dictionary<string, int>()
        {
            {"PrixPrdt",1},
            {"PrixPf",2},
            {"EuroStoxx500",3},
            {"FTSE100",4},
            {"SP500",5},
            {"HangSeng",6},
            {"Nikkei225",7},
            {"SPASX200",8},
            {"GBPEUR",9},
            {"USDEUR",10},
            {"HKDEUR",11},
            {"JPYEUR",12},
            {"AUDEUR",13},
            {"PnL",14},
            {"PnLCummule",15}
        };

        private static int GetNumberOfWorkingDays(DateTime start, DateTime stop, DateTime[] jourFeries)
        {
            DateTime tmp = start;
            int days = 0;
            while (tmp <= stop)
            {
                if (tmp.DayOfWeek != DayOfWeek.Saturday && tmp.DayOfWeek != DayOfWeek.Sunday)
                {
                    bool est_ferie = false;
                    for (int i = 0; i < jourFeries.Length; i++)
                    {
                        if (tmp.Equals(jourFeries[i]))
                        {
                            est_ferie = true;
                        }
                    }
                    if (!est_ferie)
                    {
                        ++days;
                    }
                }
                tmp = tmp.AddDays(1);
            }
            return days;
        }

        public ActionResult Index()
        {
            ViewBag.Message = "Pricer Multimonde";
            
            return View();
        }

        [HttpPost]
        public ActionResult HandleFormPrice(string date)
        {
            double prixMultimonde = 0;
            double ICMultimonde = 0;

            Price priceM2021 = new Price();
            DateTime dateTimeFin = DateTime.Parse(date, CultureInfo.CreateSpecificCulture("fr-FR"));
            DateTime dateTimeDebut = DateTime.Parse("01.10.2015", CultureInfo.CreateSpecificCulture("fr-FR"));
            int nbJourOuvre = GetNumberOfWorkingDays(dateTimeDebut, dateTimeFin, holidays);
            priceM2021.computing_multimonde(dateTimeFin.Day, dateTimeFin.Month, dateTimeFin.Year, nbJourOuvre);
            prixMultimonde = priceM2021.get_prix();
            ICMultimonde = priceM2021.get_ic();

            ViewData.Add("prixMultimonde", prixMultimonde);
            ViewData.Add("ICMultimonde", ICMultimonde);
            return View("Index");
        }


        public ActionResult About()
        {
            ViewBag.Message = "Description du produit Multimonde.";

            return View();
        }

        public ActionResult Historique()
        {
            ViewBag.Message = "Historique de performance des indices.";

            return View();
        }

        public ActionResult Change()
        {
            ViewBag.Message = "Historique de performance des changes.";

            return View();
        }

        public ActionResult Couverture()
        {
            ViewBag.Message = "Composition du portefeuille de couverture.";

            return View();
        }

        public ActionResult Forward()
        {
            ViewBag.Message = "Forward";

            return View();
        }

        [HttpPost]
        public ActionResult HandleFormForwardTest(int nbSample, int nbReb, double pas)
        {
            Price wrapper = new Price();
            wrapper.computing_forward(nbReb, nbSample, pas);
            return View("Backtest");
        }

        public ActionResult Backtest()
        {
            ViewBag.Message = "Backtesting";

            return View();
        }

        [HttpPost]
        public ActionResult HandleFormBackTest(int nbSample, int nbReb, double pas)
        {

            Price wrapper = new Price();
            wrapper.computing_back(nbReb, nbSample, pas);
            return View("Backtest");
        }

        /// <summary>
        /// Get serie in JSON format.
        /// </summary>
        /// <returns>JSON quote values.</returns>
        /// <remarks>
        /// The DateTime must be converted in Javascript date. This corresponds to total milliseconds between 01/01/1970 and current date.
        /// </remarks>
        public ActionResult GetSerie(string name)
        {
            int index = stocks[name];
            string result = "[" + String.Join(",",CSVtoJSON(index) ) + "]";
            return Content(result, "application/json");
        }

        public ActionResult GetSerieBackTest(string name)
        {
            int index = backtest[name];
            string result = "[" + String.Join(",", backtestToJson(index)) + "]";
            return Content(result, "application/json");
        }

        #region Private methods

        string[] CSVtoJSON(int underlyer)
        {
            //METTRE le chemin absolu du fichier
            string[] allLines = System.IO.File.ReadAllLines(@"C:\Users\Paul\Documents\Visual Studio 2013\Projects\ProjetEvaluationProduitStructure21\data\dataPEPS.csv");
            var initial = new DateTime(1970, 1, 1);
            List<string> listData = new List<string>();
            int ligne;
            for (ligne = 385; ligne < 835; ligne++)
            {
                string[] data = allLines[ligne].Split(',');
                string[] date = data[0].Split('/');
                var dateFormate = new DateTime(Int32.Parse(date[2]), Int32.Parse(date[1]), Int32.Parse(date[0]));
                listData.Add( "[" + (dateFormate - initial).TotalMilliseconds.ToString() + "," + data[underlyer] + "]");
            }

            return listData.ToArray();
        }

        string[] backtestToJson(int underlyer)
        {
            string[] allLines = System.IO.File.ReadAllLines(@"C:\Users\Paul\Documents\Visual Studio 2013\Projects\ProjetEvaluationProduitStructure21\data\forwardtest.csv");
            var initial = new DateTime(1970, 1, 1);
            List<string> listData = new List<string>();
            int ligne;
            for (ligne = 0; ligne < allLines.Length; ligne++)
            {
                string[] data = allLines[ligne].Split(',');
                string[] date = data[0].Split('-');
                var dateFormate = new DateTime(Int32.Parse(date[0]), Int32.Parse(date[1]), Int32.Parse(date[2]));
                listData.Add("[" + (dateFormate - initial).TotalMilliseconds.ToString() + "," + data[underlyer] + "]");
            }

            return listData.ToArray();
        }


        #endregion

    }
    
}
