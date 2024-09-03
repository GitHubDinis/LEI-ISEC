using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Identity;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.Rendering;
using Microsoft.EntityFrameworkCore;
using PWEB_2324.Data;
using PWEB_2324.Models;

namespace PWEB_2324.Controllers
{
    [Authorize("Client")]
    public class HistoricoController : Controller
    {
        private readonly ApplicationDbContext _context;
        private readonly UserManager<IdentityUser> _userManager;

        public HistoricoController(ApplicationDbContext context, UserManager<IdentityUser> userManager)
        {
            _context = context;
            _userManager = userManager;
        }
        public async Task<IActionResult> Index()
        {
            var user = await _userManager.GetUserAsync(User);

            if(user != null)
            {
                var resultado = from c in _context.Alugados
                                where c.ClienteId == user.Id
                                select c;

                return View(resultado);
            }
            return RedirectToAction("Error", "Home");
        }

        public async Task<IActionResult> AvaliaImovel(int? id)
        {

            if (id == null || _context.Alugados == null)
            {
                return NotFound();
            }

            var imoAlug = await _context.Alugados.FindAsync(id);
            if (imoAlug == null)
            {
                return NotFound();
            }

            return View(imoAlug);
        }

        [HttpPost]
        [ValidateAntiForgeryToken]
        public async Task<IActionResult> AvaliaImovel(int id, [Bind("Id,Title,Descricao,Avaliacao,ClienteId,ImovelId,LocadorId, State")] Alugado ?alug)
        {
            if (id != alug.Id)
            {
                return NotFound();
            }

            ModelState.Remove(nameof(alug.cliente));
            ModelState.Remove(nameof(alug.imovel));
            ModelState.Remove(nameof(alug.locador));
            ModelState.Remove(nameof(alug.funcionario));

            if (ModelState.IsValid)
            {
                try
                {
                    _context.Update(alug);
                    await _context.SaveChangesAsync();
                }
                catch (DbUpdateConcurrencyException)
                {
                    if (!ImovelAlugExists(alug.Id))
                    {
                        return NotFound();
                    }
                    else
                    {
                        throw;
                    }
                }
                return RedirectToAction(nameof(Index));
            }

            return View(alug);
        }

        private bool ImovelAlugExists(int id)
        {
            return (_context.Alugados?.Any(e => e.Id == id)).GetValueOrDefault();
        }
    }
}
