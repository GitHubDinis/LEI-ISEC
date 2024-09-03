using Microsoft.AspNetCore.Identity;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.ModelBinding;
using Microsoft.EntityFrameworkCore;
using PWEB_2324.Data;
using PWEB_2324.Models;

namespace PWEB_2324.Controllers
{
    public class AccountController : Controller
    {
        private readonly UserManager <IdentityUser> _userManager;
        private readonly SignInManager<IdentityUser> _signInManager;
        private readonly ApplicationDbContext _context;

        public AccountController(UserManager<IdentityUser> userManager, SignInManager<IdentityUser> signInManager, ApplicationDbContext context)
        {
            _userManager = userManager;
            _signInManager = signInManager;
            _context = context;
        }
        [HttpGet]
        public IActionResult Login(string url)
        {
            return View(new LoginModel()
            {
                Url = url
            });
        }

        [HttpPost]
        public async Task<IActionResult> Login(LoginModel loginM)
        {
            if (!ModelState.IsValid)
                return View(loginM);

            var user = await _userManager.FindByNameAsync(loginM.UserName);

            if(user != null)
            {
                if(!user.LockoutEnabled)
                {
                    var result = await _signInManager.PasswordSignInAsync(user, loginM.Password, false, false);

                    if (result.Succeeded)
                    {
                        if (string.IsNullOrEmpty(loginM.Url))
                        {
                            return RedirectToAction("Index", "Home");
                        }
                        return Redirect(loginM.Url);
                    }
                }
                else
                {
					return RedirectToAction("AccessDeniedBlock", "Account");
				}
              
            }
            ModelState.AddModelError("Password ou Username errada", "Login falhou!");
            return View(loginM);
        }

        public IActionResult Register()
        {
            return View();
        }

        [HttpPost]
        [ValidateAntiForgeryToken]
        public async Task<IActionResult> Register(LoginModel registroM)
        {
            if (ModelState.IsValid)
            {
                var user = new IdentityUser { UserName = registroM.UserName };
                var result = await _userManager.CreateAsync(user, registroM.Password);
                var userC = registroM.UserName;

                if (result.Succeeded)
                {
                    var client = new Cliente { Id = user.Id, Nome = userC };
                    _context.Add(client);
                    await _context.SaveChangesAsync();
                    // await _signInManager.SignInAsync(user, isPersistent: false);
                    await _userManager.AddToRoleAsync(user, "Client");
                    await _userManager.SetLockoutEnabledAsync(user, false);
                    
                    return RedirectToAction("Login", "Account");
                }
                else
                {
                    this.ModelState.AddModelError("Registro", "Falha ao registrar o usuário");
                }
            }
            return View(registroM);
        }

        [HttpPost]
        public async Task<IActionResult> Logout()
        {
            //HttpContext.Session.Clear();
            HttpContext.User = null;
            await _signInManager.SignOutAsync();
            return RedirectToAction("Index", "Home");
        }

        public IActionResult AccessDenied()
        {
            return View();
        }

        public IActionResult AccessDeniedBlock()
        {
            return View();
        }
    }
}
