using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Mvc;

namespace PWEB_2324.Areas.Employee.Controllers
{
    [Area("Employee")]
    [Authorize("Employee")]
    public class EmployeeController : Controller
    {
        public IActionResult Index()
        {
            return View();
        }
    }
}
