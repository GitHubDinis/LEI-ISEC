using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Identity;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using PWEB_2324.Data;
using PWEB_2324.Models;

namespace PWEB_2324.Controllers
{
    [Authorize(Roles = "Employee,Manager")]
    public class ImoveisAlugadosController : Controller
    {
        private readonly ApplicationDbContext _context;
        private readonly UserManager<IdentityUser> _userManager;

        public ImoveisAlugadosController(ApplicationDbContext context, UserManager<IdentityUser> userManager)
        {
            _context = context;
            _userManager = userManager;
        }
        public async Task<IActionResult> Index(int id, int state)
        {
            var user = await _userManager.GetUserAsync(User);
            var func = await _context.Funcionarios.FindAsync(user.Id);
            var manager = await _context.Managers.FindAsync(user.Id);
            if (id == 0 && state == 0)
            { 
                //var imo = await _context.Imoveis.FindAsync(id);
                if(func != null)
                {
                    var resultado = from c in _context.Alugados
                                    where c.LocadorId == func.LocadorId
                                    select c;
                    return View(resultado);
                }
                if(manager != null) {
                    var resultado = from c in _context.Alugados
                                    where c.LocadorId == manager.LocadorId
                                    select c;
                    return View(resultado);
                }
               
            }
            else
            {
                var imo = await _context.Alugados.FindAsync(id);
                var imoOriginal = await _context.Imoveis.FindAsync(imo.ImovelId);
                imo.State = state;
                if(state == 1 || state == 2)
                {
                    imo.FuncName = user.UserName;
                    if(state == 1)
                    {
                        imoOriginal.Available = false;
                    }
                    else
                    {
                        imoOriginal.Available = true;
                    }
                }
                _context.Update(imo);
                await _context.SaveChangesAsync();

                if (func != null)
                {
                    var resultado = from c in _context.Alugados
                                    where c.LocadorId == func.LocadorId
                                    select c;
                    return View(resultado);
                }
                if (manager != null)
                {
                    var resultado = from c in _context.Alugados
                                    where c.LocadorId == manager.LocadorId
                                    select c;
                    return View(resultado);
                }
            }

            return View();

        }
    }
}
